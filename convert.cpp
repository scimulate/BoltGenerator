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

#include "convert.h"

double degTOrad(double deg)
{
    return M_PI/180.0*deg;
}

double radTOdeg(double rad)
{
    return 180.0/M_PI*rad;
}

double inchTOmeter(double inch)
{
    return 2.54e-2*inch;
}

double convert_mm_m(double mm)
{
    return 1.0e-3*mm;
}
