/*******************************************************************************
 * jitter.cpp
 *
 * ---------------------------------------------------------------------------
 * Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
 * Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.
 *
 * POV-Ray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * POV-Ray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 * POV-Ray is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 * ---------------------------------------------------------------------------
 * $File: //depot/public/povray/3.x/source/backend/support/jitter.cpp $
 * $Revision: #1 $
 * $Change: 6069 $
 * $DateTime: 2013/11/06 11:59:40 $
 * $Author: chrisc $
 *******************************************************************************/

// frame.h must always be the first POV file included (pulls in platform config)
#include "backend/frame.h"
#include "backend/support/jitter.h"

// this must be the last file included
#include "base/povdebug.h"

namespace pov
{

const float JitterTable[256] =
{
	-0.500000,  0.005890,  0.011749, -0.490234,  0.023468, -0.470703, -0.480469,  0.017609,
	 0.046906, -0.447266, -0.441406,  0.056671, -0.460938,  0.044952,  0.035187, -0.466797,
	 0.093781, -0.400391, -0.394531,  0.103546, -0.382813,  0.123077,  0.113312, -0.388672,
	-0.421875,  0.084015,  0.089874, -0.412109,  0.070343, -0.423828, -0.433594,  0.064484,
	 0.187531, -0.306641, -0.300781,  0.197296, -0.289063,  0.216827,  0.207062, -0.294922,
	-0.265625,  0.240265,  0.246124, -0.255859,  0.226593, -0.267578, -0.277344,  0.220734,
	-0.343750,  0.162140,  0.167999, -0.333984,  0.179718, -0.314453, -0.324219,  0.173859,
	 0.140656, -0.353516, -0.347656,  0.150421, -0.367188,  0.138702,  0.128937, -0.373047,
	 0.375031, -0.119141, -0.113281,  0.384796, -0.101563,  0.404327,  0.394562, -0.107422,
	-0.078125,  0.427765,  0.433624, -0.068359,  0.414093, -0.080078, -0.089844,  0.408234,
	-0.031250,  0.474640,  0.480499, -0.021484,  0.492218, -0.001953, -0.011719,  0.486359,
	 0.453156, -0.041016, -0.035156,  0.462921, -0.054688,  0.451202,  0.441437, -0.060547,
	-0.187500,  0.318390,  0.324249, -0.177734,  0.335968, -0.158203, -0.167969,  0.330109,
	 0.359406, -0.134766, -0.128906,  0.369171, -0.148438,  0.357452,  0.347687, -0.154297,
	 0.281281, -0.212891, -0.207031,  0.291046, -0.195313,  0.310577,  0.300812, -0.201172,
	-0.234375,  0.271515,  0.277374, -0.224609,  0.257843, -0.236328, -0.246094,  0.251984,
	-0.249969,  0.255859,  0.261719, -0.240204,  0.273438, -0.220673, -0.230438,  0.267578,
	 0.296875, -0.197235, -0.191376,  0.306641, -0.210907,  0.294922,  0.285156, -0.216766,
	 0.343750, -0.150360, -0.144501,  0.353516, -0.132782,  0.373047,  0.363281, -0.138641,
	-0.171844,  0.333984,  0.339844, -0.162079,  0.320313, -0.173798, -0.183563,  0.314453,
	 0.437500, -0.056610, -0.050751,  0.447266, -0.039032,  0.466797,  0.457031, -0.044891,
	-0.015594,  0.490234,  0.496094, -0.005829,  0.476563, -0.017548, -0.027313,  0.470703,
	-0.093719,  0.412109,  0.417969, -0.083954,  0.429688, -0.064423, -0.074188,  0.423828,
	 0.390625, -0.103485, -0.097626,  0.400391, -0.117157,  0.388672,  0.378906, -0.123016,
	 0.125000, -0.369110, -0.363251,  0.134766, -0.351532,  0.154297,  0.144531, -0.357391,
	-0.328094,  0.177734,  0.183594, -0.318329,  0.164063, -0.330048, -0.339813,  0.158203,
	-0.281219,  0.224609,  0.230469, -0.271454,  0.242188, -0.251923, -0.261688,  0.236328,
	 0.203125, -0.290985, -0.285126,  0.212891, -0.304657,  0.201172,  0.191406, -0.310516,
	-0.437469,  0.068359,  0.074219, -0.427704,  0.085938, -0.408173, -0.417938,  0.080078,
	 0.109375, -0.384735, -0.378876,  0.119141, -0.398407,  0.107422,  0.097656, -0.404266,
	 0.031250, -0.462860, -0.457001,  0.041016, -0.445282,  0.060547,  0.050781, -0.451141,
	-0.484344,  0.021484,  0.027344, -0.474579,  0.007813, -0.486298, -0.496063,  0.001953,
};

}
