/**************************************************/
/*
/*	SPH�@�̏������q�z�u�o�̓v���O����
/*	�d�v�Ȃ̂͒萔��SPH�@�̃\�[�X�ƈ�v���Ă��邱��
/*
/**************************************************/

#include <fstream>
#include <cmath>

static const double SPH_SIMSCALE    = 0.004;		// �V�~�����[�V�����̃X�P�[��
static const double SPH_RESTDENSITY = 1000.0;	// ��햧�x
static const double SPH_PMASS       = 0.00020543;	// ���q��̎��� 
static const double SPH_PDIST       = pow(SPH_PMASS / SPH_RESTDENSITY, 1.0/3.0 );
static const char*	oFileName = "../init2.txt";

typedef struct{
	double x;
	double y;
	double z;
}vec3;
vec3 INIT_MIN, INIT_MAX;

int main(){
	INIT_MIN.x = 0.0;
	INIT_MIN.y = 10.0;
	INIT_MIN.z = 0.0;
	INIT_MAX.x = 20.0;
	INIT_MAX.y = 10.0;
	INIT_MAX.z = 20.0;

	
	std::ofstream ofs(oFileName);
	double d = SPH_PDIST / SPH_SIMSCALE * 0.95;
	double y = 10.0;
	int count = 0;
	for ( double x = INIT_MIN.x+d; x <= INIT_MAX.x-d; x += d )
	for(double y = 10.0;y <= 10.0+2*d;y+=d)
	for ( double z = INIT_MIN.z+d; z <= INIT_MAX.z-d; z += d )
	{
		count++;
	}
	ofs << count << "\n";
	for ( double x = INIT_MIN.x+d; x <= INIT_MAX.x-d; x += d )
	for(double y = 10.0;y <= 10.0+2*d;y+=d)
	for ( double z = INIT_MIN.z+d; z <= INIT_MAX.z-d; z += d )
	{
		ofs << x << "\t" << y << "\t" << z << "\n";
	}
}