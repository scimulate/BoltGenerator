/*
    BoltGenerator is an automated CAD assistant which produces standard-size 3D
    bolts per ISO and ASME specifications.
    Copyright (C) 2021  Scimulate LLC <solvers@scimulate.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "bolt.h"

#include <iostream>

Bolt::Bolt(std::string head_,
           double majord_, 
           double length_,
           double pitch_,
           double pitchd_): head(head_),
                            majord(majord_),
                            length(length_),
                            pitch(pitch_),
                            pitchd(pitchd_)
{
    body = Shank();

    /*
    TopExp_Explorer map(BRepAlgoAPI_Fuse(Shank(indexThread, length, simple),
                                         Head(indexHead, indexThread)),
                        TopAbs_SOLID);
    body = TopoDS::Solid(map.Current());
    */
}

TopoDS_Solid Bolt::Shank()
{
    TopoDS_Solid mask, shank, thread, fullshank;
    gp_Trsf offset;

    // The geometry kernel has issues building threads unevenly. The applied
    // work-around creates an integer number of complete threads, later trimmed.
    // Add extra length (2*pitch) to clean up partial threads.
    // Round up to nearest full thread.
    double nthreads = std::ceil((length + 2*pitch)/pitch);
    
    // Start with a cylinder
    shank = BRepPrimAPI_MakeCylinder(0.5*majord, pitch*nthreads);

    // Create a 3D body of threads, cut them from the cylinder.
    thread = Thread(majord-2.0*3.0/8.0*pitch, pitch, pitch*nthreads);
    shank = Cut(shank, thread);

    // Remove head-side partial thread
    mask = BRepPrimAPI_MakeCylinder(majord, pitch).Solid();
    shank = Cut(shank, mask);

    // Remove end-side partial thread
    offset.SetTranslation(gp_Vec(0.0, 0.0, length+pitch));
    mask = BRepPrimAPI_MakeCylinder(majord, nthreads*pitch-pitch-length).Solid();
    shank = Cut(shank, BRepBuilderAPI_Transform(mask, offset).Shape());

    // Currently the shank is floating off of the origin by dz=pitch. Shift down.
    offset.SetTranslation(gp_Vec(0.0, 0.0, -pitch));
    shank = TopoDS::Solid(BRepBuilderAPI_Transform(shank, offset));

    // Chamfer lead-in thread
    double x[] = {0.5*majord-pitch,
                  majord};
    double z[] = {length,
                  length-0.5*majord-pitch};
    std::vector<gp_Pnt> points = {gp_Pnt(x[0], 0.0, z[0]),
                                  gp_Pnt(x[1], 0.0, z[0]),
                                  gp_Pnt(x[1], 0.0, z[1])};
    shank = Cut(shank, Chamfer(points));

    return shank;
}

TopoDS_Solid Bolt::Solid()
{
    return body;
}

/*
TopoDS_Solid Bolt::Head(int indexHead, int indexThread)
{
    TopoDS_Solid output;
    double thickness = dimensions.GetHeadDims(indexHead, indexThread).at(0);
    gp_Trsf offset;

    if(indexHead == 1) // 1 == Hex Bolt
    {
        double aflats = dimensions.GetHeadDims(indexHead, indexThread).at(1);
        double acorners = 1.1*aflats;
        TopoDS_Solid tool = Cut(BRepPrimAPI_MakeCylinder(acorners, thickness).Solid(),
                                BRepPrimAPI_MakeCylinder(0.5*acorners, thickness).Solid());
        output = Cut(Hexagon(aflats, thickness), tool);
    }
    else if(indexHead == 2) // 2 == SHCS
    {
        double aflats = dimensions.GetHeadDims(indexHead, indexThread).at(2);
        double diam = dimensions.GetHeadDims(indexHead, indexThread).at(1);
        output = Cut(BRepPrimAPI_MakeCylinder(0.5*diam, thickness).Solid(), Hexagon(aflats, aflats));
    }

    offset.SetTranslation(gp_Vec(0.0, 0.0, -thickness));
    return TopoDS::Solid(BRepBuilderAPI_Transform(output, offset));
}

TopoDS_Solid Bolt::Shank(int indexThread, double length, bool simple)
{

}
*/