/* MDH WCET BENCHMARK SUITE. File version $Id: ludcmp.c,v 1.2 2006/01/27 13:15:28 jgn Exp $ */

/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: ludcmp.c                                                       */
/*  SOURCE : Turbo C Programming for Engineering                         */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Simultaneous linear equations by LU decomposition.                */
/*     The arrays a[][] and b[] are input and the array x[] is output    */
/*     row vector.                                                       */
/*     The variable n is the number of equations.                        */
/*     The input arrays are initialized in function main.                */
/*                                                                       */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/


/* Changes:
 * JG 2005/12/12: Indented program. Removed unused variable nmax.
 */

/*
** Benchmark Suite for Real-Time Applications, by Sung-Soo Lim
**
**    III-4. ludcmp.c : Simultaneous Linear Equations by LU Decomposition
**                 (from the book C Programming for EEs by Hyun Soon Ahn)
*/


#ifdef TEST
    #include "../mini_printf.h"
    #include "../posix_c.h"
#else
    #include <stdio.h>
#endif



int             ludcmp(double a[][50], double b[], double x[], /* int nmax, */ int n, double eps);


static double
t_fabs(double n)
{
	double          f;

	if (n >= 0)
		f = n;
	else
		f = -n;
	return f;
}

int
main(void)
{

	int             i, j/*, nmax = 50*/, n = 47, chkerr;
	double          eps, w;
	double          a[50][50], b[50], x[50];
	double res_a[50][50] = {
		{20.000000, 3.000000, 4.000000, 5.000000, 6.000000, 7.000000, 8.000000, 9.000000,
		10.000000, 11.000000, 12.000000, 13.000000, 14.000000, 15.000000, 16.000000, 17.000000,
		18.000000, 19.000000, 20.000000, 21.000000, 22.000000, 23.000000, 24.000000, 25.000000,
		26.000000, 27.000000, 28.000000, 29.000000, 30.000000, 31.000000, 32.000000, 33.000000,
		34.000000, 35.000000, 36.000000, 37.000000, 38.000000, 39.000000, 40.000000, 41.000000,
		42.000000, 43.000000, 44.000000, 45.000000, 46.000000, 47.000000, 48.000000, 49.000000},
		{0.150000, 39.550000, 4.400000, 5.250000, 6.100000, 6.950000, 7.800000, 8.650000,
		9.500000, 10.350000, 11.200000, 12.050000, 12.900000, 13.750000, 14.600000, 15.450000,
		16.300000, 17.150000, 18.000000, 18.850000, 19.700000, 20.550000, 21.400000, 22.250000,
		23.100000, 23.950000, 24.800000, 25.650000, 26.500000, 27.350000, 28.200000, 29.050000,
		29.900000, 30.750000, 31.600000, 32.450000, 33.300000, 34.150000, 35.000000, 35.850000,
		36.700000, 37.550000, 38.400000, 39.250000, 40.100000, 40.950000, 41.800000, 42.650000},
		{0.200000, 0.111252, 58.710493, 5.415929, 6.121365, 6.826802, 7.532238, 8.237674,
		8.943110, 9.648546, 10.353982, 11.059418, 11.764855, 12.470291, 13.175727, 13.881163,
		14.586599, 15.292035, 15.997472, 16.702908, 17.408344, 18.113780, 18.819216, 19.524652,
		20.230088, 20.935525, 21.640961, 22.346397, 23.051833, 23.757269, 24.462705, 25.168142,
		25.873578, 26.579014, 27.284450, 27.989886, 28.695322, 29.400759, 30.106195, 30.811631,
		31.517067, 32.222503, 32.927939, 33.633375, 34.338812, 35.044248, 35.749684, 36.455120},
		{0.250000, 0.132743, 0.092248, 77.553488, 6.125581, 6.697674, 7.269767, 7.841860,
		8.413953, 8.986047, 9.558140, 10.130233, 10.702326, 11.274419, 11.846512, 12.418605,
		12.990698, 13.562791, 14.134884, 14.706977, 15.279070, 15.851163, 16.423256, 16.995349,
		17.567442, 18.139535, 18.711628, 19.283721, 19.855814, 20.427907, 21.000000, 21.572093,
		22.144186, 22.716279, 23.288372, 23.860465, 24.432558, 25.004651, 25.576744, 26.148837,
		26.720930, 27.293023, 27.865116, 28.437209, 29.009302, 29.581395, 30.153488, 30.725581},
		{0.300000, 0.154235, 0.104264, 0.078985, 96.137100, 6.587262, 7.037424, 7.487585,
		7.937747, 8.387909, 8.838071, 9.288233, 9.738395, 10.188557, 10.638719, 11.088881,
		11.539043, 11.989205, 12.439367, 12.889529, 13.339691, 13.789852, 14.240014, 14.690176,
		15.140338, 15.590500, 16.040662, 16.490824, 16.940986, 17.391148, 17.841310, 18.291472,
		18.741634, 19.191796, 19.641958, 20.092119, 20.542281, 20.992443, 21.442605, 21.892767,
		22.342929, 22.793091, 23.243253, 23.693415, 24.143577, 24.593739, 25.043901, 25.494063},
		{0.350000, 0.175727, 0.116279, 0.086362, 0.068519, 114.505104, 6.843456, 7.181809,
		7.520162, 7.858514, 8.196867, 8.535220, 8.873573, 9.211925, 9.550278, 9.888631,
		10.226983, 10.565336, 10.903689, 11.242041, 11.580394, 11.918747, 12.257100, 12.595452,
		12.933805, 13.272158, 13.610510, 13.948863, 14.287216, 14.625568, 14.963921, 15.302274,
		15.640627, 15.978979, 16.317332, 16.655685, 16.994037, 17.332390, 17.670743, 18.009096,
		18.347448, 18.685801, 19.024154, 19.362506, 19.700859, 20.039212, 20.377564, 20.715917},
		{0.400000, 0.197219, 0.128295, 0.093739, 0.073202, 0.059766, 132.689734, 6.924793,
		7.159851, 7.394910, 7.629969, 7.865027, 8.100086, 8.335144, 8.570203, 8.805262,
		9.040320, 9.275379, 9.510438, 9.745496, 9.980555, 10.215613, 10.450672, 10.685731,
		10.920789, 11.155848, 11.390906, 11.625965, 11.861024, 12.096082, 12.331141, 12.566200,
		12.801258, 13.036317, 13.271375, 13.506434, 13.741493, 13.976551, 14.211610, 14.446669,
		14.681727, 14.916786, 15.151844, 15.386903, 15.621962, 15.857020, 16.092079, 16.327138},
		{0.450000, 0.218710, 0.140310, 0.101116, 0.077884, 0.062720, 0.052188, 150.714389,
		6.853109, 6.991828, 7.130547, 7.269267, 7.407986, 7.546705, 7.685425, 7.824144,
		7.962863, 8.101583, 8.240302, 8.379021, 8.517741, 8.656460, 8.795179, 8.933899,
		9.072618, 9.211338, 9.350057, 9.488776, 9.627496, 9.766215, 9.904934, 10.043654,
		10.182373, 10.321092, 10.459812, 10.598531, 10.737250, 10.875970, 11.014689, 11.153409,
		11.292128, 11.430847, 11.569567, 11.708286, 11.847005, 11.985725, 12.124444, 12.263163},
		{0.500000, 0.240202, 0.152326, 0.108492, 0.082567, 0.065675, 0.053959, 0.045471,
		168.595723, 6.643646, 6.691569, 6.739492, 6.787416, 6.835339, 6.883262, 6.931185,
		6.979108, 7.027032, 7.074955, 7.122878, 7.170801, 7.218725, 7.266648, 7.314571,
		7.362494, 7.410417, 7.458341, 7.506264, 7.554187, 7.602110, 7.650033, 7.697957,
		7.745880, 7.793803, 7.841726, 7.889649, 7.937573, 7.985496, 8.033419, 8.081342,
		8.129265, 8.177189, 8.225112, 8.273035, 8.320958, 8.368881, 8.416805, 8.464728},
		{0.550000, 0.261694, 0.164341, 0.115869, 0.087249, 0.068630, 0.055731, 0.046391,
		0.039406, 186.345155, 6.306574, 6.267992, 6.229411, 6.190829, 6.152248, 6.113667,
		6.075085, 6.036504, 5.997923, 5.959341, 5.920760, 5.882178, 5.843597, 5.805016,
		5.766434, 5.727853, 5.689271, 5.650690, 5.612109, 5.573527, 5.534946, 5.496364,
		5.457783, 5.419202, 5.380620, 5.342039, 5.303457, 5.264876, 5.226295, 5.187713,
		5.149132, 5.110551, 5.071969, 5.033388, 4.994806, 4.956225, 4.917644, 4.879062},
		{0.600000, 0.283186, 0.176357, 0.123246, 0.091932, 0.071585, 0.057502, 0.047312,
		0.039690, 0.033844, 203.969926, 5.848021, 5.726115, 5.604210, 5.482304, 5.360399,
		5.238493, 5.116588, 4.994683, 4.872777, 4.750872, 4.628966, 4.507061, 4.385155,
		4.263250, 4.141345, 4.019439, 3.897534, 3.775628, 3.653723, 3.531817, 3.409912,
		3.288006, 3.166101, 3.044196, 2.922290, 2.800385, 2.678479, 2.556574, 2.434668,
		2.312763, 2.190858, 2.068952, 1.947047, 1.825141, 1.703236, 1.581330, 1.459425},
		{0.650000, 0.304678, 0.188372, 0.130623, 0.096614, 0.074540, 0.059274, 0.048232,
		0.039974, 0.033636, 0.028671, 221.473809, 5.270761, 5.067713, 4.864665, 4.661617,
		4.458569, 4.255521, 4.052473, 3.849424, 3.646376, 3.443328, 3.240280, 3.037232,
		2.834184, 2.631136, 2.428088, 2.225040, 2.021992, 1.818944, 1.615896, 1.412848,
		1.209800, 1.006752, 0.803704, 0.600656, 0.397608, 0.194560, -0.008488, -0.211536,
		-0.414584, -0.617632, -0.820680, -1.023728, -1.226776, -1.429824, -1.632872, -1.835920},
		{0.700000, 0.326169, 0.200388, 0.137999, 0.101297, 0.077495, 0.061045, 0.049152,
		0.040259, 0.033429, 0.028073, 0.023799, 238.857565, 4.574639, 4.291713, 4.008786,
		3.725860, 3.442934, 3.160007, 2.877081, 2.594154, 2.311228, 2.028302, 1.745375,
		1.462449, 1.179522, 0.896596, 0.613670, 0.330743, 0.047817, -0.235110, -0.518036,
		-0.800962, -1.083889, -1.366815, -1.649742, -1.932668, -2.215594, -2.498521, -2.781447,
		-3.064374, -3.347300, -3.630226, -3.913153, -4.196079, -4.479006, -4.761932, -5.044858},
		{0.750000, 0.347661, 0.212403, 0.145376, 0.105979, 0.080450, 0.062817, 0.050073,
		0.040543, 0.033222, 0.027476, 0.022882, 0.019152, 256.119202, 3.756797, 3.394393,
		3.031988, 2.669584, 2.307179, 1.944775, 1.582370, 1.219966, 0.857561, 0.495157,
		0.132752, -0.229652, -0.592057, -0.954461, -1.316866, -1.679270, -2.041675, -2.404079,
		-2.766484, -3.128889, -3.491293, -3.853698, -4.216102, -4.578507, -4.940911, -5.303316,
		-5.665720, -6.028125, -6.390529, -6.752934, -7.115338, -7.477743, -7.840147, -8.202552},
		{0.800000, 0.369153, 0.224419, 0.152753, 0.110662, 0.083405, 0.064588, 0.050993,
		0.040827, 0.033015, 0.026878, 0.021965, 0.017968, 0.014668, 273.254055, 2.811735,
		2.369414, 1.927094, 1.484773, 1.042453, 0.600132, 0.157811, -0.284509, -0.726830,
		-1.169150, -1.611471, -2.053792, -2.496112, -2.938433, -3.380753, -3.823074, -4.265395,
		-4.707715, -5.150036, -5.592356, -6.034677, -6.476998, -6.919318, -7.361639, -7.803959,
		-8.246280, -8.688601, -9.130921, -9.573242, -10.015562, -10.457883, -10.900204, -11.342524},
		{0.850000, 0.390645, 0.236434, 0.160130, 0.115344, 0.086360, 0.066360, 0.051914,
		0.041111, 0.032808, 0.026280, 0.021048, 0.016783, 0.013253, 0.010290, 290.254737,
		1.731223, 1.207710, 0.684196, 0.160682, -0.362832, -0.886346, -1.409860, -1.933374,
		-2.456888, -2.980402, -3.503915, -4.027429, -4.550943, -5.074457, -5.597971, -6.121485,
		-6.644999, -7.168513, -7.692027, -8.215540, -8.739054, -9.262568, -9.786082, -10.309596,
		-10.833110, -11.356624, -11.880138, -12.403652, -12.927165, -13.450679, -13.974193, -14.497707},
		{0.900000, 0.412137, 0.248450, 0.167506, 0.120027, 0.089315, 0.068131, 0.052834,
		0.041396, 0.032601, 0.025683, 0.020131, 0.015599, 0.011838, 0.008671, 0.005964,
		307.110923, 0.504071, -0.102781, -0.709633, -1.316485, -1.923337, -2.530189, -3.137042,
		-3.743894, -4.350746, -4.957598, -5.564450, -6.171302, -6.778154, -7.385006, -7.991858,
		-8.598710, -9.205562, -9.812414, -10.419266, -11.026118, -11.632971, -12.239823, -12.846675,
		-13.453527, -14.060379, -14.667231, -15.274083, -15.880935, -16.487787, -17.094639, -17.701491},
		{0.950000, 0.433628, 0.260465, 0.174883, 0.124709, 0.092270, 0.069903, 0.053755,
		0.041680, 0.032394, 0.025085, 0.019215, 0.014414, 0.010423, 0.007052, 0.004161,
		0.001641, 323.808987, -0.884274, -1.577535, -2.270796, -2.964057, -3.657318, -4.350579,
		-5.043840, -5.737101, -6.430362, -7.123623, -7.816884, -8.510145, -9.203406, -9.896667,
		-10.589927, -11.283188, -11.976449, -12.669710, -13.362971, -14.056232, -14.749493, -15.442754,
		-16.136015, -16.829276, -17.522537, -18.215798, -18.909059, -19.602320, -20.295581, -20.988842},
		{1.000000, 0.455120, 0.272481, 0.182260, 0.129392, 0.095224, 0.071674, 0.054675,
		0.041964, 0.032187, 0.024487, 0.018298, 0.013230, 0.009008, 0.005434, 0.002357,
		-0.000335, -0.002731, 340.331446, -2.452312, -3.236071, -4.019829, -4.803587, -5.587345,
		-6.371103, -7.154861, -7.938620, -8.722378, -9.506136, -10.289894, -11.073652, -11.857411,
		-12.641169, -13.424927, -14.208685, -14.992443, -15.776201, -16.559960, -17.343718, -18.127476,
		-18.911234, -19.694992, -20.478751, -21.262509, -22.046267, -22.830025, -23.613783, -24.397542},
		{1.050000, 0.476612, 0.284496, 0.189637, 0.134074, 0.098179, 0.073446, 0.055595,
		0.042248, 0.031980, 0.023890, 0.017381, 0.012045, 0.007593, 0.003815, 0.000554,
		-0.002311, -0.004872, -0.007206, 356.656171, -4.223323, -5.102817, -5.982311, -6.861805,
		-7.741299, -8.620793, -9.500287, -10.379781, -11.259275, -12.138769, -13.018263, -13.897757,
		-14.777251, -15.656745, -16.536239, -17.415733, -18.295227, -19.174721, -20.054215, -20.933709,
		-21.813203, -22.692697, -23.572191, -24.451685, -25.331179, -26.210673, -27.090167, -27.969661},
		{1.100000, 0.498104, 0.296512, 0.197013, 0.138757, 0.101134, 0.075217, 0.056516,
		0.042533, 0.031773, 0.023292, 0.016464, 0.010861, 0.006178, 0.002196, -0.001250,
		-0.004287, -0.007013, -0.009509, -0.011841, 372.755279, -6.226522, -7.208324, -8.190126,
		-9.171927, -10.153729, -11.135531, -12.117333, -13.099134, -14.080936, -15.062738, -16.044539,
		-17.026341, -18.008143, -18.989944, -19.971746, -20.953548, -21.935349, -22.917151, -23.898953,
		-24.880754, -25.862556, -26.844358, -27.826159, -28.807961, -29.789763, -30.771564, -31.753366},
		{1.150000, 0.519595, 0.308527, 0.204390, 0.143439, 0.104089, 0.076989, 0.057436,
		0.042817, 0.031566, 0.022694, 0.015547, 0.009676, 0.004763, 0.000578, -0.003054,
		-0.006263, -0.009154, -0.011812, -0.014307, -0.016704, 388.593606, -8.498658, -9.590922,
		-10.683186, -11.775449, -12.867713, -13.959977, -15.052241, -16.144504, -17.236768, -18.329032,
		-19.421296, -20.513559, -21.605823, -22.698087, -23.790351, -24.882614, -25.974878, -27.067142,
		-28.159406, -29.251669, -30.343933, -31.436197, -32.528461, -33.620724, -34.712988, -35.805252},
		{1.200000, 0.541087, 0.320543, 0.211767, 0.148122, 0.107044, 0.078760, 0.058357,
		0.043101, 0.031359, 0.022097, 0.014631, 0.008492, 0.003348, -0.001041, -0.004857,
		-0.008239, -0.011295, -0.014114, -0.016773, -0.019338, -0.021870, 404.126562, -11.086238,
		-12.299038, -13.511838, -14.724637, -15.937437, -17.150237, -18.363037, -19.575837, -20.788637,
		-22.001437, -23.214237, -24.427036, -25.639836, -26.852636, -28.065436, -29.278236, -30.491036,
		-31.703836, -32.916636, -34.129435, -35.342235, -36.555035, -37.767835, -38.980635, -40.193435},
		{1.250000, 0.562579, 0.332558, 0.219144, 0.152804, 0.109999, 0.080532, 0.059277,
		0.043385, 0.031152, 0.021499, 0.013714, 0.007307, 0.001933, -0.002660, -0.006661,
		-0.010215, -0.013436, -0.016417, -0.019239, -0.021972, -0.024681, -0.027433, 419.297120,
		-14.048668, -15.394457, -16.740245, -18.086033, -19.431821, -20.777610, -22.123398, -23.469186,
		-24.814974, -26.160763, -27.506551, -28.852339, -30.198127, -31.543916, -32.889704, -34.235492,
		-35.581280, -36.927069, -38.272857, -39.618645, -40.964433, -42.310222, -43.656010, -45.001798},
		{1.300000, 0.584071, 0.344574, 0.226520, 0.157487, 0.112954, 0.082303, 0.060197,
		0.043670, 0.030945, 0.020901, 0.012797, 0.006123, 0.000518, -0.004279, -0.008465,
		-0.012191, -0.015577, -0.018720, -0.021705, -0.024606, -0.027492, -0.030434, -0.033505,
		434.031481, -17.462756, -18.956993, -20.451230, -21.945467, -23.439704, -24.933941, -26.428178,
		-27.922415, -29.416652, -30.910890, -32.405127, -33.899364, -35.393601, -36.887838, -38.382075,
		-39.876312, -41.370549, -42.864786, -44.359023, -45.853260, -47.347497, -48.841734, -50.335971},
		{1.350000, 0.605563, 0.356589, 0.233897, 0.162169, 0.115909, 0.084075, 0.061118,
		0.043954, 0.030738, 0.020304, 0.011880, 0.004938, -0.000897, -0.005897, -0.010268,
		-0.014167, -0.017718, -0.021023, -0.024171, -0.027240, -0.030303, -0.033435, -0.036715,
		-0.040234, 448.232736, -21.429297, -23.091331, -24.753364, -26.415397, -28.077430, -29.739464,
		-31.401497, -33.063530, -34.725563, -36.387597, -38.049630, -39.711663, -41.373696, -43.035730,
		-44.697763, -46.359796, -48.021829, -49.683862, -51.345896, -53.007929, -54.669962, -56.331995},
		{1.400000, 0.627054, 0.368605, 0.241274, 0.166852, 0.118864, 0.085846, 0.062038,
		0.044238, 0.030531, 0.019706, 0.010963, 0.003754, -0.002312, -0.007516, -0.012072,
		-0.016143, -0.019859, -0.023326, -0.026637, -0.029874, -0.033114, -0.036436, -0.039925,
		-0.043677, -0.047808, 461.771347, -26.082967, -27.937281, -29.791595, -31.645908, -33.500222,
		-35.354536, -37.208850, -39.063164, -40.917478, -42.771792, -44.626106, -46.480420, -48.334734,
		-50.189047, -52.043361, -53.897675, -55.751989, -57.606303, -59.460617, -61.314931, -63.169245},
		{1.450000, 0.648546, 0.380620, 0.248651, 0.171534, 0.121819, 0.087618, 0.062959,
		0.044522, 0.030324, 0.019108, 0.010047, 0.002569, -0.003727, -0.009135, -0.013875,
		-0.018119, -0.021999, -0.025629, -0.029103, -0.032507, -0.035924, -0.039437, -0.043134,
		-0.047119, -0.051516, -0.056485, 474.470449, -31.607589, -33.685627, -35.763666, -37.841704,
		-39.919742, -41.997781, -44.075819, -46.153857, -48.231895, -50.309934, -52.387972, -54.466010,
		-56.544049, -58.622087, -60.700125, -62.778164, -64.856202, -66.934240, -69.012278, -71.090317},
		{1.500000, 0.670038, 0.392636, 0.256027, 0.176217, 0.124774, 0.089389, 0.063879,
		0.044807, 0.030117, 0.018511, 0.009130, 0.001385, -0.005142, -0.010753, -0.015679,
		-0.020095, -0.024140, -0.027932, -0.031569, -0.035141, -0.038735, -0.042438, -0.046344,
		-0.050562, -0.055224, -0.060500, -0.066617, 486.082353, -38.260547, -40.603448, -42.946348,
		-45.289249, -47.632150, -49.975050, -52.317951, -54.660851, -57.003752, -59.346653, -61.689553,
		-64.032454, -66.375354, -68.718255, -71.061156, -73.404056, -75.746957, -78.089857, -80.432758},
		{1.550000, 0.691530, 0.404651, 0.263404, 0.180899, 0.127729, 0.091161, 0.064799,
		0.045091, 0.029910, 0.017913, 0.008213, 0.000200, -0.006557, -0.012372, -0.017483,
		-0.022071, -0.026281, -0.030235, -0.034035, -0.037775, -0.041546, -0.045439, -0.049553,
		-0.054005, -0.058932, -0.064516, -0.070996, -0.078712, 496.249454, -46.413393, -49.076240,
		-51.739087, -54.401934, -57.064781, -59.727627, -62.390474, -65.053321, -67.716168, -70.379015,
		-73.041862, -75.704709, -78.367555, -81.030402, -83.693249, -86.356096, -89.018943, -91.681790},
		{1.600000, 0.713021, 0.416667, 0.270781, 0.185582, 0.130683, 0.092932, 0.065720,
		0.045375, 0.029703, 0.017315, 0.007296, -0.000984, -0.007972, -0.013991, -0.019286,
		-0.024047, -0.028422, -0.032538, -0.036501, -0.040409, -0.044357, -0.048440, -0.052763,
		-0.057447, -0.062640, -0.068532, -0.075376, -0.083532, -0.093528, 504.435967, -56.622756,
		-59.681478, -62.740201, -65.798924, -68.857647, -71.916370, -74.975093, -78.033816, -81.092539,
		-84.151262, -87.209985, -90.268708, -93.327431, -96.386154, -99.444877, -102.503600, -105.562323},
		{1.650000, 0.734513, 0.428682, 0.278158, 0.190264, 0.133638, 0.094704, 0.066640,
		0.045659, 0.029496, 0.016718, 0.006379, -0.002169, -0.009387, -0.015610, -0.021090,
		-0.026023, -0.030563, -0.034841, -0.038967, -0.043043, -0.047168, -0.051441, -0.055973,
		-0.060890, -0.066348, -0.072547, -0.079756, -0.088352, -0.098894, -0.112250, 509.801525,
		-69.761652, -73.324829, -76.888005, -80.451182, -84.014358, -87.577535, -91.140712, -94.703888,
		-98.267065, -101.830241, -105.393418, -108.956595, -112.519771, -116.082948, -119.646124, -123.209301},
		{1.700000, 0.756005, 0.440698, 0.285534, 0.194947, 0.136593, 0.096475, 0.067561,
		0.045944, 0.029289, 0.016120, 0.005462, -0.003353, -0.010802, -0.017228, -0.022894,
		-0.027999, -0.032704, -0.037144, -0.041433, -0.045677, -0.049978, -0.054442, -0.059182,
		-0.064333, -0.070056, -0.076563, -0.084135, -0.093172, -0.104260, -0.118313, -0.136841,
		510.949270, -87.281154, -91.511579, -95.742004, -99.972428, -104.202853, -108.433278, -112.663702,
		-116.894127, -121.124552, -125.354976, -129.585401, -133.815826, -138.046250, -142.276675, -146.507100},
		{1.750000, 0.777497, 0.452713, 0.292911, 0.199629, 0.139548, 0.098247, 0.068481,
		0.046228, 0.029082, 0.015522, 0.004546, -0.004538, -0.012217, -0.018847, -0.024697,
		-0.029975, -0.034845, -0.039447, -0.043899, -0.048311, -0.052789, -0.057443, -0.062392,
		-0.067775, -0.073764, -0.080579, -0.088515, -0.097992, -0.109626, -0.124377, -0.143830,
		-0.170822, 505.374353, -111.783283, -116.940920, -122.098557, -127.256194, -132.413831, -137.571468,
		-142.729104, -147.886741, -153.044378, -158.202015, -163.359652, -168.517288, -173.674925, -178.832562},
		{1.800000, 0.798989, 0.464729, 0.300288, 0.204312, 0.142503, 0.100018, 0.069402,
		0.046512, 0.028874, 0.014925, 0.003629, -0.005722, -0.013632, -0.020466, -0.026501,
		-0.031951, -0.036986, -0.041750, -0.046365, -0.050945, -0.055600, -0.060444, -0.065602,
		-0.071218, -0.077472, -0.084594, -0.092895, -0.102812, -0.114992, -0.130441, -0.150819,
		-0.179101, -0.221189, 488.094249, -148.443791, -154.981831, -161.519871, -168.057911, -174.595951,
		-181.133992, -187.672032, -194.210072, -200.748112, -207.286152, -213.824192, -220.362232, -226.900272},
		{1.850000, 0.820480, 0.476744, 0.307665, 0.208994, 0.145458, 0.101790, 0.070322,
		0.046796, 0.028667, 0.014327, 0.002712, -0.006907, -0.015046, -0.022084, -0.028305,
		-0.033927, -0.039127, -0.044052, -0.048831, -0.053579, -0.058411, -0.063445, -0.068811,
		-0.074661, -0.081180, -0.088610, -0.097274, -0.107632, -0.120358, -0.136504, -0.157809,
		-0.187381, -0.231395, -0.304129, 447.579826, -209.238851, -218.057528, -226.876205, -235.694881,
		-244.513558, -253.332235, -262.150912, -270.969589, -279.788266, -288.606943, -297.425620, -306.244297},
		{1.900000, 0.841972, 0.488760, 0.315041, 0.213677, 0.148413, 0.103561, 0.071242,
		0.047081, 0.028460, 0.013729, 0.001795, -0.008091, -0.016461, -0.023703, -0.030108,
		-0.035903, -0.041268, -0.046355, -0.051297, -0.056213, -0.061222, -0.066446, -0.072021,
		-0.078103, -0.084888, -0.092625, -0.101654, -0.112452, -0.125724, -0.142568, -0.164798,
		-0.195660, -0.241600, -0.317524, -0.467489, 349.745711, -329.575408, -342.896528, -356.217648,
		-369.538768, -382.859888, -396.181007, -409.502127, -422.823247, -436.144367, -449.465487, -462.786607},
		{1.950000, 0.863464, 0.500775, 0.322418, 0.218359, 0.151368, 0.105333, 0.072163,
		0.047365, 0.028253, 0.013132, 0.000878, -0.009276, -0.017876, -0.025322, -0.031912,
		-0.037879, -0.043409, -0.048658, -0.053762, -0.058847, -0.064032, -0.069447, -0.075230,
		-0.081546, -0.088596, -0.096641, -0.106034, -0.117272, -0.131090, -0.148632, -0.171788,
		-0.203940, -0.251806, -0.330919, -0.487192, -0.942329, 29.981559, -680.445993, -706.873544,
		-733.301096, -759.728648, -786.156200, -812.583751, -839.011303, -865.438855, -891.866407, -918.293958},
		{2.000000, 0.884956, 0.512791, 0.329795, 0.223042, 0.154323, 0.107104, 0.073083,
		0.047649, 0.028046, 0.012534, -0.000038, -0.010460, -0.019291, -0.026941, -0.033715,
		-0.039855, -0.045550, -0.050961, -0.056228, -0.061480, -0.066843, -0.072448, -0.078440,
		-0.084989, -0.092304, -0.100657, -0.110414, -0.122092, -0.136456, -0.154695, -0.178777,
		-0.212219, -0.262011, -0.344314, -0.506896, -0.980417, -22.695484, -15448.985636, -16778.260200,
		-17405.534764, -18032.809328, -18660.083892, -19287.358456, -19914.633019, -20541.907583, -21169.182147, -21796.456711},
		{2.050000, 0.906448, 0.524806, 0.337172, 0.227724, 0.157278, 0.108876, 0.074004,
		0.047933, 0.027839, 0.011936, -0.000955, -0.011645, -0.020706, -0.028559, -0.035519,
		-0.041831, -0.047691, -0.053264, -0.058694, -0.064114, -0.069654, -0.075449, -0.081650,
		-0.088432, -0.096012, -0.104672, -0.114793, -0.126912, -0.141822, -0.160759, -0.185766,
		-0.220499, -0.272217, -0.357710, -0.526599, -1.018505, -23.576944, 1.086043, 1512.018786,
		821.635500, 851.252214, 880.868928, 910.485641, 940.102355, 969.719069, 999.335783, 1028.952497},
		{2.100000, 0.927939, 0.536822, 0.344548, 0.232407, 0.160233, 0.110647, 0.074924,
		0.048218, 0.027632, 0.011339, -0.001872, -0.012829, -0.022121, -0.030178, -0.037323,
		-0.043807, -0.049832, -0.055567, -0.061160, -0.066748, -0.072465, -0.078450, -0.084859,
		-0.091874, -0.099720, -0.108688, -0.119173, -0.131732, -0.147188, -0.166822, -0.192756,
		-0.228778, -0.282423, -0.371105, -0.546302, -1.056593, -24.458404, 1.126646, 0.543403,
		1143.886477, 420.522816, 435.159155, 449.795494, 464.431832, 479.068171, 493.704510, 508.340848},
		{2.150000, 0.949431, 0.548837, 0.351925, 0.237089, 0.163187, 0.112419, 0.075844,
		0.048502, 0.027425, 0.010741, -0.002789, -0.014014, -0.023536, -0.031797, -0.039126,
		-0.045783, -0.051973, -0.057870, -0.063626, -0.069382, -0.075276, -0.081451, -0.088069,
		-0.095317, -0.103428, -0.112704, -0.123553, -0.136552, -0.152554, -0.172886, -0.199745,
		-0.237058, -0.292628, -0.384500, -0.566005, -1.094681, -25.339865, 1.167249, 0.562991,
		0.367626, 1037.097202, 290.886153, 300.675105, 310.464057, 320.253008, 330.041960, 339.830912},
		{2.200000, 0.970923, 0.560853, 0.359302, 0.241772, 0.166142, 0.114190, 0.076765,
		0.048786, 0.027218, 0.010143, -0.003706, -0.015198, -0.024951, -0.033416, -0.040930,
		-0.047759, -0.054114, -0.060173, -0.066092, -0.072016, -0.078087, -0.084452, -0.091279,
		-0.098760, -0.107136, -0.116719, -0.127932, -0.141372, -0.157920, -0.178950, -0.206734,
		-0.245337, -0.302834, -0.397895, -0.585708, -1.132769, -26.221325, 1.207852, 0.582578,
		0.380422, 0.280481, 993.433081, 226.822457, 234.211834, 241.601211, 248.990588, 256.379964},
		{2.250000, 0.992415, 0.572868, 0.366679, 0.246454, 0.169097, 0.115962, 0.077685,
		0.049070, 0.027011, 0.009546, -0.004622, -0.016383, -0.026366, -0.035034, -0.042734,
		-0.049735, -0.056255, -0.062476, -0.068558, -0.074650, -0.080897, -0.087453, -0.094488,
		-0.102202, -0.110844, -0.120735, -0.132312, -0.146192, -0.163286, -0.185013, -0.213724,
		-0.253617, -0.313039, -0.411290, -0.605411, -1.170857, -27.102785, 1.248455, 0.602166,
		0.393217, 0.289920, 0.228322, 974.676961, 188.632827, 194.588692, 200.544558, 206.500424},
		{2.300000, 1.013906, 0.584884, 0.374055, 0.251137, 0.172052, 0.117733, 0.078606,
		0.049355, 0.026804, 0.008948, -0.005539, -0.017567, -0.027781, -0.036653, -0.044537,
		-0.051711, -0.058396, -0.064779, -0.071024, -0.077284, -0.083708, -0.090454, -0.097698,
		-0.105645, -0.114552, -0.124751, -0.136692, -0.151012, -0.168652, -0.191077, -0.220713,
		-0.261896, -0.323245, -0.424685, -0.625114, -1.208945, -27.984245, 1.289058, 0.621753,
		0.406012, 0.299359, 0.235760, 0.193534, 968.280567, 163.282453, 168.284339, 173.286226},
		{2.350000, 1.035398, 0.596899, 0.381432, 0.255819, 0.175007, 0.119504, 0.079526,
		0.049639, 0.026597, 0.008350, -0.006456, -0.018752, -0.029196, -0.038272, -0.046341,
		-0.053687, -0.060537, -0.067082, -0.073490, -0.079918, -0.086519, -0.093455, -0.100907,
		-0.109088, -0.118260, -0.128766, -0.141071, -0.155832, -0.174018, -0.197141, -0.227702,
		-0.270176, -0.333450, -0.438080, -0.644817, -1.247033, -28.865706, 1.329661, 0.641341,
		0.418807, 0.308797, 0.243198, 0.199644, 0.168631, 968.912087, 145.232786, 149.553484},
		{2.400000, 1.056890, 0.608915, 0.388809, 0.260502, 0.177962, 0.121276, 0.080446,
		0.049923, 0.026390, 0.007753, -0.007373, -0.019936, -0.030611, -0.039890, -0.048145,
		-0.055663, -0.062678, -0.069385, -0.075956, -0.082552, -0.089330, -0.096457, -0.104117,
		-0.112530, -0.121968, -0.132782, -0.145451, -0.160651, -0.179383, -0.203204, -0.234692,
		-0.278456, -0.343656, -0.451475, -0.664520, -1.285121, -29.747166, 1.370264, 0.660928,
		0.431603, 0.318236, 0.250636, 0.205755, 0.173797, 0.149893, 973.920608, 131.730115},
		{2.450000, 1.078382, 0.620930, 0.396186, 0.265184, 0.180917, 0.123047, 0.081367,
		0.050207, 0.026183, 0.007155, -0.008290, -0.021121, -0.032026, -0.041509, -0.049948,
		-0.057639, -0.064819, -0.071688, -0.078422, -0.085186, -0.092141, -0.099458, -0.107327,
		-0.115973, -0.125676, -0.136798, -0.149831, -0.165471, -0.184749, -0.209268, -0.241681,
		-0.286735, -0.353862, -0.464870, -0.684223, -1.323209, -30.628626, 1.410867, 0.680516,
		0.444398, 0.327675, 0.258075, 0.211866, 0.178963, 0.154352, 0.135258, 981.839310}
	};

	double res_b[] = {
		1242.000000, 1308.000000, 1374.000000, 1440.000000, 1506.000000, 1572.000000, 1638.000000, 1704.000000,
		1770.000000, 1836.000000, 1902.000000, 1968.000000, 2034.000000, 2100.000000, 2166.000000, 2232.000000,
		2298.000000, 2364.000000, 2430.000000, 2496.000000, 2562.000000, 2628.000000, 2694.000000, 2760.000000,
		2826.000000, 2892.000000, 2958.000000, 3024.000000, 3090.000000, 3156.000000, 3222.000000, 3288.000000,
		3354.000000, 3420.000000, 3486.000000, 3552.000000, 3618.000000, 3684.000000, 3750.000000, 3816.000000,
		3882.000000, 3948.000000, 4014.000000, 4080.000000, 4146.000000, 4212.000000, 4278.000000, 4344.000000
	};

	double res_x[] = {

		1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
		1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
		1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
		1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
		1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
		1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000
	};

	eps = 1.0e-6;

	for (i = 0; i <= n; i++) {
		w = 0.0;
		for (j = 0; j <= n; j++) {
			a[i][j] = (i + 1) + (j + 1);
			if (i == j)
				a[i][j] *= 10.0;
			w += a[i][j];
		}
		b[i] = w;
	}

	chkerr = ludcmp(a, b, x, /* nmax, */ n, eps);
	// for(int i = 0; i <=n; i++){
	// 	printf("{");
	// 	for(int j = 0; j <= n; j++){
	// 		if(j != n)
	// 			printf("%lf, ", a[i][j]);
	// 		if(j == n)
	// 			printf("%lf}, ", a[i][j]);
	// 		if((j + 1) % 8 == 0)
	// 			printf("\n");
	// 	}
	// }
	//
#ifdef TEST
	for(int i = 0; i <=n; i++){
		for(int j = 0; j <= n; j++){
			if(t_fabs(a[i][j] - res_a[i][j]) > 0.001){
				j = 0;
	            memcpy(out_mem, &j, sizeof(int));
	            return 0;
			}
		}
		//printf("\n");
	}

	for(int j = 0; j <= n; j++){
		if(t_fabs(b[j] - res_b[j]) > 0.001){
			j = 0;
            memcpy(out_mem, &j, sizeof(int));
            return 0;
		}
	}
	for(int j = 0; j <= n; j++){
		if(t_fabs(x[j] - res_x[j]) > 0.001){
			j = 0;
            memcpy(out_mem, &j, sizeof(int));
            return 0;
		}
	}
	j = 1;
	memcpy(out_mem, &j, sizeof(int));
#endif
	return 0;

}

int
ludcmp(double a[][50], double b[], double x[], /* int nmax, */ int n, double eps)
{

	int             i, j, k;
	double          w, y[100];

	if (n > 99 || eps <= 0.0)
		return (999);
	for (i = 0; i < n; i++) {
		if (t_fabs(a[i][i]) <= eps)
			return (1);
		for (j = i + 1; j <= n; j++) {
			w = a[j][i];
			if (i != 0)
				for (k = 0; k < i; k++)
					w -= a[j][k] * a[k][i];
			a[j][i] = w / a[i][i];
		}
		for (j = i + 1; j <= n; j++) {
			w = a[i + 1][j];
			for (k = 0; k <= i; k++)
				w -= a[i + 1][k] * a[k][j];
			a[i + 1][j] = w;
		}
	}
	y[0] = b[0];
	for (i = 1; i <= n; i++) {
		w = b[i];
		for (j = 0; j < i; j++)
			w -= a[i][j] * y[j];
		y[i] = w;
	}
	x[n] = y[n] / a[n][n];
	for (i = n - 1; i >= 0; i--) {
		w = y[i];
		for (j = i + 1; j <= n; j++)
			w -= a[i][j] * x[j];
		x[i] = w / a[i][i];
	}
	return (0);

}