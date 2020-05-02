#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//---�萔
static const char* iFileName = "./init2.txt";
static const double dt = 0.0001;
static const double springConst = 30.0;
static const double springConst2 = 1000.0;
static const double dampingConst = 10.0;
static const double mass = 0.00020543;
static const double SPH_SIMSCALE    = 0.004;		// �V�~�����[�V�����̃X�P�[��
static const double SPH_RESTDENSITY = 1000.0;	// ���햧�x
static const double d =  pow(mass / SPH_RESTDENSITY, 1.0f/3.0 );
static const double h = d * 0.95 * 2.1;
static const double min_x = 2.0;
static const double max_x = 18.0;
static const double min_z = 2.0;
static const double max_z = 18.0;

static const double epsilon = 1e-4;
static const double gravity_x = 0.0;
static const double gravity_y = -9.8;
static const double gravity_z = 0.0;

//---�ϐ�
int pSize;
double t = 0;
double t_end;
double ot = 0.1;

typedef struct
{
	double x;
	double y;
	double z;
	double vx;
	double vy;
	double vz;
	double fx;
	double fy;
	double fz;
}PARTICLE;

PARTICLE p0[507];	//�������q�z�u
PARTICLE p[507];	//�X�V���q�z�u
PARTICLE ball;		//�O�G
//PARTICLE p0[169];	//�������q�z�u
//PARTICLE p[169];	//�X�V���q�z�u

void init()
{
	ifstream ifs(iFileName);

	ifs >> pSize;
	//p0	= new PARTICLE[pSize];
	//p	= new PARTICLE[pSize];
	int i = 0;
	while(ifs){
		ifs >> p0[i].x >> p0[i].y >> p0[i].z ;
		p[i].x = p0[i].x;p[i].y = p0[i].y;p[i].z = p0[i].z;
		p[i].fx = 0.0;p[i].fy = 0.0;p[i].fz = 0.0;
		p[i].vx = 0.0;p[i].vy = 0.0;p[i].vz = 0.0;
		i++;
	}

	//---�{�[���̏�����
	ball.x = 10.0;ball.y = 30.0;ball.z = 10.0;
	ball.fx = 0.0;ball.fy = 0.0;ball.fz = 0.0;
	ball.vx = 0.0;ball.vy = 0.0;ball.vz = 0.0;
}
double dist(PARTICLE pi, PARTICLE pj)
{
	double dist = sqrt(pow(pi.x - pj.x, 2.0) + pow(pi.y - pj.y, 2.0) + pow(pi.z - pj.z, 2.0));
	return dist;
}
double dist2(PARTICLE pi, PARTICLE pj)
{
	double dist2 = pow(pi.x - pj.x, 2.0) + pow(pi.y - pj.y, 2.0) + pow(pi.z - pj.z, 2.0);
	return dist2;
}
void cal_force()
{
	//---�͂��[���ɐݒ�
	for(int i = 0;i< pSize;i++){
		p[i].fx = p[i].fy = p[i].fz = 0.0;
	}
	ball.fx = ball.fy = ball.fz = 0.0;

	//---�͂��v�Z
	for(int i = 0;i< pSize-1;i++){
		for(int j = i+1;j < pSize;j++){
			double r_ij = dist(p[i], p[j]);
			double r0_ij = dist(p0[i], p0[j]);

			if (r0_ij > h / SPH_SIMSCALE) continue;
			PARTICLE pi_n1, pj_n1;
			pi_n1.x = p[i].x + p[i].vx * dt;
			pi_n1.y = p[i].y + p[i].vy * dt;
			pi_n1.z = p[i].z + p[i].vz * dt;

			pj_n1.x = p[j].x + p[j].vx * dt;
			pj_n1.y = p[j].y + p[j].vy * dt;
			pj_n1.z = p[j].z + p[j].vz * dt;
			double dl_ij = r_ij - dist(pi_n1, pj_n1);
			p[i].fx += -springConst * (r_ij - r0_ij) * SPH_SIMSCALE * (p[i].x - p[j].x) / r_ij + dampingConst * dl_ij * (p[i].x - p[j].x) * SPH_SIMSCALE / (dt * r_ij);
			p[i].fy += -springConst * (r_ij - r0_ij) * SPH_SIMSCALE * (p[i].y - p[j].y) / r_ij + dampingConst * dl_ij * (p[i].y - p[j].y) * SPH_SIMSCALE / (dt * r_ij);
			p[i].fz += -springConst * (r_ij - r0_ij) * SPH_SIMSCALE * (p[i].z - p[j].z) / r_ij + dampingConst * dl_ij * (p[i].z - p[j].z) * SPH_SIMSCALE / (dt * r_ij);

			p[j].fx += -springConst * (r_ij - r0_ij) * SPH_SIMSCALE * (p[j].x - p[i].x) / r_ij + dampingConst * dl_ij * (p[j].x - p[i].x) * SPH_SIMSCALE / (dt * r_ij);
			p[j].fy += -springConst * (r_ij - r0_ij) * SPH_SIMSCALE * (p[j].y - p[i].y) / r_ij + dampingConst * dl_ij * (p[j].y - p[i].y) * SPH_SIMSCALE / (dt * r_ij);
			p[j].fz += -springConst * (r_ij - r0_ij) * SPH_SIMSCALE * (p[j].z - p[i].z) / r_ij + dampingConst * dl_ij * (p[j].z - p[i].z) * SPH_SIMSCALE / (dt * r_ij);
			//cout << -springConst * (r_ij -  r0_ij) * (p[j].x - p[i].x) / r_ij << ", " << dampingConst * dl_ij * (p[j].x - p[i].x) / (dt * r_ij) << "\n";
		}
	}
	for(int i = 0;i < pSize;i++){
		p[i].fy += gravity_y * mass;
	}
	ball.fy += gravity_y * mass;
}
void cal_ext(){
	//---�y�i���e�B�@
	for(int i = 0;i < pSize;i++){
		double r_pb = dist(p[i], ball);
		if(r_pb < d){
			//---���܂����f�ʂ肵�Ă�
			ball.fx = - springConst2 * (d - r_pb) * SPH_SIMSCALE * (p[i].x - ball.x) / r_pb;
			ball.fy = - springConst2 * (d - r_pb) * SPH_SIMSCALE * (p[i].y - ball.y) / r_pb;
			ball.fz = - springConst2 * (d - r_pb) * SPH_SIMSCALE * (p[i].z - ball.z) / r_pb;

			p[i].fx = - springConst2 * (d - r_pb) * SPH_SIMSCALE * (ball.x - p[i].x) / r_pb;
			p[i].fy = - springConst2 * (d - r_pb) * SPH_SIMSCALE * (ball.y - p[i].y) / r_pb;
			p[i].fz = - springConst2 * (d - r_pb) * SPH_SIMSCALE * (ball.z - p[i].z) / r_pb;

		}
	}
}
void update(){
	for(int i = 0;i < pSize;i++){
		if(p[i].x < min_x || p[i].x > max_x|| p[i].z < min_z || p[i].z > max_z)continue;
		p[i].vx += (p[i].fx / mass) * dt;
		p[i].vy += (p[i].fy / mass) * dt;
		p[i].vz += (p[i].fz / mass) * dt;
	}
	for(int i = 0;i < pSize;i++){
		p[i].x += p[i].vx * dt;
		p[i].y += p[i].vy * dt;
		p[i].z += p[i].vz * dt;
	}
	ball.vx += (ball.fx / mass) * dt;
	ball.vy += (ball.fy / mass) * dt;
	ball.vz += (ball.fz / mass) * dt;
	ball.x += ball.vx * dt;
	ball.y += ball.vy * dt;
	ball.z += ball.vz * dt;
	t+= dt;
}
void output_obj(int cnt)
{
	char file_name[19];
	sprintf(file_name, "result%08d.obj", cnt);
	//cout << "processing " << file_name << " ..." << endl;
	ofstream ofs( file_name );
	if ( ! ofs )
    {
      cerr << "cannot open " << file_name << endl;
      exit(1);
    }
	for(int i = 0;i< pSize;i++){
		ofs << "v " << p[i].x << " " << p[i].y << " " << p[i].z << "\n";
	}
	ofs << "v " << ball.x << " " << ball.y << " " << ball.z << "\n";
}
int main()
{
	cout << "�V�~�����[�V�������ԁF";
	cin >> t_end;
	//---�������q�z�u
	init();

	int count = 0;
	double t_next = 0.0;

	//---simulation
	while(t < t_end){
		//---output objfile
		//0.1s���Ƃɕ`��
		if(t > t_next-epsilon && t < t_next + epsilon){
			cout << t << "�b" << endl;
			output_obj(count);
			count++;
			t_next += ot;
		}

		//---�o�l�_���p���f���K��
		cal_force();

		//---�O�͌v�Z
		cal_ext();

		//---�ʒu���x�X�V
		update();
	}
}
