#ifndef INCLUDED_OBJLOADER_H
#define INCLUDED_OBJLOADER_H

#include <fstream>
#include <string>
#include <vector>
#include "Vector3D.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

class ObjLoader{
private:
	Vector3D *mPos;		//頂点座標値データ
	Vector3D *mNorm;	//頂点法線ベクトルデータ
	Vector3D *mFacePos;	//テクスチャ座標値データ(番号)
	int		 *mFaceNorm;//テクスチャ法線データ(番号)
	int		 mVertexSize;	//頂点データ数
	int		 mNormSize;		//法線ベクトルデータ数
	int		 mFaceSize;		//テクスチャデータ数
public:
    ObjLoader(const char *);
	~ObjLoader();
	int getVertexSize();
	int getNormSize();
	int getFaceSize();
	void cpyData(Vector3D *);
	void cpyData(Vector3D *, Vector3D *);
	void cpyData(Vector3D *, Vector3D *, Vector3D *, int *);
	void cpyData(Vector3D *vert, Vector3D *tri, Vector3D *normal);
};
//コンストラクタ
ObjLoader::ObjLoader(const char *fileName){
    double x, y, z, xx;
	std::vector<Vector3D>	v, vn, f;
	std::vector<int>		fn;

	std::ifstream ifs(fileName);
	std::string buf;	/*一行データ*/
	/*ファイル読み込み*/
	while(ifs && getline(ifs, buf) ){
		//頂点座標値データ読込
		if(buf.at(0) == 'v' && buf.at(1) ==' '){
			Vector3D temp;
			std::vector<std::string> str;	/*区分データ*/
			
			boost::algorithm::split(str, buf, boost::algorithm::is_space() );

			x = boost::lexical_cast<double>(str[1]);
			y = boost::lexical_cast<double>(str[2]);
			z = boost::lexical_cast<double>(str[3]);
			temp.x=x;temp.y=y;temp.z=z;
			v.push_back(temp);
		}
		//頂点法線ベクトルデータ読込
		if(buf.at(0) == 'v' && buf.at(1) == 'n'){
			Vector3D temp;
			std::vector<std::string> str;	/*区分データ*/
			
			boost::algorithm::split(str, buf, boost::algorithm::is_space() );

			x = boost::lexical_cast<double>(str[1]);
			y = boost::lexical_cast<double>(str[2]);
			z = boost::lexical_cast<double>(str[3]);
			temp.x=x;temp.y=y;temp.z=z;
			vn.push_back(temp);
		}
		//壁面情報読み込み
		if(buf.at(0) == 'f'){
			Vector3D temp;
			std::vector<std::string> str;	/*区分データ*/

			boost::algorithm::split(str, buf, boost::algorithm::is_space() );
			std::string str_x  = str[1].substr(0, str[1].find("/"));
			std::string str_xx = str[1].substr(str[1].rfind("/")+1);
			std::string str_y  = str[2].substr(0, str[2].find("/"));
			std::string str_z  = str[3].substr(0, str[3].find("/"));
			x  = boost::lexical_cast<int>(str_x )-1;
			xx = boost::lexical_cast<int>(str_xx)-1;
			y  = boost::lexical_cast<int>(str_y )-1;
			z  = boost::lexical_cast<int>(str_z )-1;
			temp.x=x;temp.y=y;temp.z=z;
			f.push_back(temp);
			fn.push_back(xx);
		}
	}
	mVertexSize  = v.size();
	mPos  = new Vector3D[mVertexSize];

	mNormSize = vn.size();
	mNorm = new Vector3D[mNormSize];

	mFaceSize = f.size();
	mFacePos  = new Vector3D[mFaceSize];
	mFaceNorm = new int[mFaceSize];

	for(int i=0;i<mVertexSize;i++){
		mPos[i]	 = v[i];
	}
	for(int i=0;i<mNormSize;i++){
		mNorm[i] = vn[i]; 
	}
	for(int i=0;i<mFaceSize;i++){
		mFacePos[i]=f[i];
		mFaceNorm[i]=fn[i];
	}
}
int ObjLoader::getVertexSize(){
	return mVertexSize;
}
int ObjLoader::getNormSize(){
	return mNormSize;
}
int ObjLoader::getFaceSize(){
	return mFaceSize;
}
//頂点座標値データ取り出し
void ObjLoader::cpyData(Vector3D *v){
	for(int i=0;i<mVertexSize;i++){
		v[i]  = mPos[i];
	}
}
//頂点座標値、頂点法線ベクトルデータ取り出し
void ObjLoader::cpyData(Vector3D *v, Vector3D *vn){
	for(int i=0;i<mVertexSize;i++){
		v[i]  = mPos[i];
	}
	for(int i=0;i<mNormSize;i++){
		vn[i] = mNorm[i];
	}
}

void ObjLoader::cpyData(Vector3D *v, Vector3D *vn, Vector3D *f, int *fn){
	for(int i=0;i<mVertexSize;i++){
		v[i]  = mPos[i];
	}
	for(int i=0;i<mNormSize;i++){
		vn[i] = mNorm[i];
	}
	for(int i=0;i<mFaceSize;i++){
		f[i]  = mFacePos[i];
		fn[i] = mFaceNorm[i];
	}
}
void ObjLoader::cpyData(Vector3D *vert, Vector3D *tri, Vector3D *normal){
	
	for(int i = 0;i < mVertexSize; i++){
		vert[i] = mPos[i];
	}
	for(int i = 0;i < mFaceSize; i++){
		tri[i]  = mFacePos[i];
		normal[i] = mNorm[ mFaceNorm[i] ];
	}
}
//デストラクタ
ObjLoader::~ObjLoader(){
	delete[] mPos;
	delete[] mNorm;
	delete[] mFacePos;
	delete[] mFaceNorm;
}

#endif
