#include "math.h"

typedef struct {
	double x,
	double y,
}index;


index get_inflection_point(index p0, index p1, index p2, int instance)
{
	index pp1 = {p1.x - p0.x, p1.y - p0.y};
	index pp2 = {p2.x - p0.x, p2.y - p0.y};
	
	double pp1v = sqrt(pp1.x*pp1.x + pp1.y+pp1.y);
	double pp2v = sqrt(pp2.x*pp2.x + pp2.y+pp2.y);

	float sin = (pp1.x*pp2.y - pp2.x*pp1.y) / (pp1v * ppv2));

	double pfv = instance / sin;
	double pev = instance / sin;

	double pec = pev / pp1v;
	index pe = {pec*pp1.x, pec*pp1.y};

	double pfc = pfv / pp2v;
	index pf = {pfc*pp2.x, pfc*pp2.y};

	index pq = {pe.x + pf.x, pe.y + pf.y};
	
	return pq;
}
