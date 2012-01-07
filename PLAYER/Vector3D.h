#ifndef INCLUDED_VECTOR3D_H
#define INCLUDED_VECTOR3D_H

class Vector3D{
public:
	//メンバ変数
	double x;
	double y;
	double z;
	//コンストラクタ
	Vector3D();
	Vector3D(double x,double y,double z);
	//代入演算子
	Vector3D& Vector3D::operator=(const Vector3D& v);
	//単項演算子
	Vector3D& operator+=(const Vector3D& v);
	Vector3D& operator-=(const Vector3D& v);
	Vector3D& operator*=(double k);
	Vector3D& operator/=(double k);
	Vector3D operator+()const;
	Vector3D operator-()const;
	//添え字演算子
	double& operator[](int i);
    //比較演算子
	bool operator==(const Vector3D& v ) const;
	bool operator!=(const Vector3D& v ) const;
	//べクトルの長さ
	double norm()const;
	//正規化
	Vector3D normalize();
	//ゼロベクトル代入
	void zero();
};
//ベクトル演算
//Vector3D+Vector3D
Vector3D operator+(const Vector3D& u,const Vector3D& v);
//Vector3D-Vector3D
Vector3D operator-(const Vector3D& u,const Vector3D& v);
//double*Vector3D
Vector3D operator*(double k,const  Vector3D& v);
//Vector3D*double
Vector3D operator*(const Vector3D& v,double k);
//Vector3D/double
Vector3D operator/(const Vector3D& v,double k);
//内積 Vector3D*Vector3D
double operator*(const Vector3D& u,const Vector3D& v);
//外積 Vector3D%Vector3D
Vector3D operator%(const Vector3D& u,const Vector3D& v);
//2つのベクトルのなす角度
double angle(const Vector3D& u,const Vector3D& v);
//出力
#include <iostream>
inline std::ostream& operator<<(std::ostream& s, const Vector3D& v);
//*----------------------メンバ関数の実装--------------------------*//
#include <cmath>
//コンストラクタ
inline Vector3D::Vector3D(){ x = y = z = 0; }
inline Vector3D::Vector3D(double x,double y,double z){
	this->x=x;		this->y=y;		this->z=z;
}
//代入演算子
inline Vector3D& Vector3D::operator=(const Vector3D& v){
	this->x=v.x;	this->y=v.y;	this->z=v.z;
	return *this;
}
//単項演算子
inline Vector3D& Vector3D::operator+=(const Vector3D& v){
	 this->x += v.x;	this->y += v.y;		this->z += v.z;
	 return *this;
}
inline Vector3D& Vector3D::operator-=(const Vector3D& v){
	 this->x -= v.x;	this->y -= v.y;		this->z -= v.z;
	 return *this;
}
inline Vector3D& Vector3D::operator*=(double k){
	 this->x *= k;		this->y *= k;		this->z *= k;
	 return *this;
}
inline Vector3D& Vector3D::operator/=(double k){
	this->x /= k;		this->y /= k;		this->z /= k;
	return *this;
}
inline Vector3D Vector3D::operator+()const{		//+Vector3D
	return *this;
}
inline Vector3D Vector3D::operator-()const{		//-Vector3D
	return Vector3D(-x,-y,-z);
}
//添え字演算子
inline double& Vector3D::operator[](int i){
	if(i == 0){
		return x;
	}
	else if(i == 1){
		return y;
	}
	else if(i == 2){
		return z;
	}
	else{
		return x;
	}
}
//比較演算子
inline bool Vector3D::operator==(const Vector3D& v ) const{
    return (x == v.x) && (y == v.y) && (z == v.z);
}
inline bool Vector3D::operator!=(const Vector3D& v ) const{
    return !(*this == v);
}
//べクトルの長さ
inline double Vector3D::norm()const{
	return pow(x*x+y*y+z*z,0.5);
}
//正規化
inline Vector3D Vector3D::normalize(){
	Vector3D u;
	//u.x = this->x / norm();
	//u.y = this->y / norm();
	//u.z = this->z / norm();
	u = *this/norm();
	return u;
}
//ゼロベクトル代入
inline void Vector3D::zero(){
	Vector3D zero;
	*this = zero;
}
//*----------------------グローバル関数の実装--------------------------*//
//二項演算子の定義
//Vector3D+Vector3D
inline Vector3D operator+(const Vector3D& u,const Vector3D& v){
	Vector3D w;
	w.x=u.x+v.x;
	w.y=u.y+v.y;
	w.z=u.z+v.z;
	return w;
}
//Vector3D-Vector3D
inline Vector3D operator-(const Vector3D& u,const Vector3D& v){
	Vector3D w;
	w.x=u.x-v.x;
	w.y=u.y-v.y;
	w.z=u.z-v.z;
	return w;
}
//double*Vector3D
inline Vector3D operator*(double k,const  Vector3D& v){
	return Vector3D(k*v.x,k*v.y,k*v.z);
}
//Vector3D*double
inline Vector3D operator*(const Vector3D& v,double k){
	return Vector3D(v.x*k,v.y*k,v.z*k);
}
//Vector3D/double
inline Vector3D operator/(const Vector3D& v,double k){
	return Vector3D(v.x/k,v.y/k,v.z/k);
}
//内積 Vector3D*Vector3D
inline double operator*(const Vector3D& u,const Vector3D& v){
	return u.x*v.x+u.y*v.y+u.z*v.z;
}
//外積 Vector3D%Vector3D
inline Vector3D operator%(const Vector3D& u,const Vector3D& v){
	Vector3D w;
	w.x=u.y*v.z-u.z*v.y;
	w.y=u.z*v.x-u.x*v.z;
	w.z=u.x*v.y-u.y*v.x;
	return w;
}
//画面への表示
#include <iostream>
inline std::ostream& operator<<(std::ostream& s, const Vector3D& v){
	return s <<'('<<v.x<<","<<v.y<<","<<v.z<<')';
}

#define my_PI 3.1415926535
//2つのベクトルのなす角
inline double angle(const Vector3D& u,const Vector3D& v){
	double cos =u*v/(u.norm()*v.norm());
	return double(acos(cos)/my_PI*180);
}

#endif