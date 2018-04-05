#ifndef POINT3_H
#define POINT3_H

#include <iostream>
#include <Eigen/Dense>

#include "Line.h"
#include "Point2.h"

#define PI 3.14159265

using namespace Eigen;
using namespace std;

class Point3{
	public:

	int m_index;// index of the point
	Vector3f m_coordinates;// Cordinates of the point (x, y, z)
		
	Point3(double x, double y, double z,int index){
		m_index = index;
		m_coordinates<< x, y, z;	
	}

	Point3(){
		m_index = -1;
		m_coordinates<< 0.0, 0.0, 0.0;
	}
	
	// returns the projection of the point on the XY plane
	Point2 projectOnXY(){
		return Point2(m_coordinates(0), m_coordinates(1), m_index, true, false, false, false);	
	}
	
	// returns the projection of the point on the YZ plane
	Point2 projectOnYZ(){
		return Point2(m_coordinates(1), m_coordinates(2), m_index, false, true, false, false);	
	}
	
	// returns the projection of the point on the XZ plane
	Point2 projectOnXZ(){
		return Point2(m_coordinates(0), m_coordinates(2), m_index, false, false, true, false);	
	}

	// returns the isometric view of the point
	Point2 isoView(){
		Matrix3f isoMatrix;
		isoMatrix(0, 0) = sqrt(3);
		isoMatrix(0, 1) = 0.0;
		isoMatrix(0, 2) = -sqrt(3);

		isoMatrix(1, 0) = 1;
		isoMatrix(1, 1) = 2;
		isoMatrix(1, 2) = 1;

		isoMatrix(2, 0) = sqrt(2);
		isoMatrix(2, 1) = -sqrt(2);
		isoMatrix(2, 2) = sqrt(2);

		Vector3f isoVec = isoMatrix * m_coordinates;
		
		return Point2(isoVec(0), isoVec(1), m_index, false, false, false, true);
	}
	
	// regenerates the point given 3 projections
	void regenerate3(Point2 &pointxy, Point2 &pointyz, Point2 &pointxz){
		if(m_index!=-1){
			cout<<"\nWARNING : Overwriting an aldready existing Point.";
			return;
		}
			
		if(!(pointxy.m_OnXY && pointyz.m_OnYZ && pointxz.m_OnXZ)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points which are not on XY, YZ or XZ plane.";
			return;
		}
		
		if(!((pointxy.m_index == pointyz.m_index) && (pointyz.m_index == pointxz.m_index))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose indexes does not match";
			return;
		}
		
		if(!(pointxy.m_coordinates(0)==pointxz.m_coordinates(0))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose X-Coordinate do not match";
			return;
		}
		else{
			m_coordinates(0) = pointxy.m_coordinates(0);
		}
		
		if(!(pointxy.m_coordinates(1)==pointyz.m_coordinates(0))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose Y-Coordinate do not match";
			return;
		}
		else{
			m_coordinates(1) = pointxy.m_coordinates(1);
		}
		
		if(!(pointxz.m_coordinates(1)==pointyz.m_coordinates(1))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose Z-Coordinate do not match";
			return;
		}
		else{
			m_coordinates(2) = pointxz.m_coordinates(1);
		}
		
		m_index = pointxy.m_index;
		
		return;
	}

	// regenerates the point given 2 projections: XY and YZ
	void regenerate2_XY_YZ(Point2 &pointxy, Point2 &pointyz){
		if(m_index!=-1){
			cout<<"\nWARNING : Overwriting an aldready existing Point.";
			return;
		}
			
		if(!(pointxy.m_OnXY && pointyz.m_OnYZ)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points which are not on XY, YZ plane.";
			return;
		}
		
		if(!(pointxy.m_index == pointyz.m_index)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose indexes does not match";
			return;
		}
		
		if(!(pointxy.m_coordinates(1)==pointyz.m_coordinates(0))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose Y-Coordinate do not match";
			return;
		}
		else{
			m_coordinates(0) = pointxy.m_coordinates(0);
			m_coordinates(1) = pointxy.m_coordinates(1);
			m_coordinates(2) = pointyz.m_coordinates(1);
		}
		
		m_index = pointxy.m_index;
		return;
	}
	
	// regenerates the point given 2 projections: YZ and XZ
	void regenerate2_YZ_XZ(Point2 &pointyz, Point2 &pointxz){
		if(m_index!=-1){
			cout<<"\nWARNING : Overwriting an aldready existing Point.";
			return;
		}
			
		if(!(pointyz.m_OnYZ && pointxz.m_OnXZ)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points which are not on XY, YZ plane.";
			return;
		}
		
		if(!(pointyz.m_index == pointxz.m_index)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose indexes does not match";
			return;
		}
		
		if(!(pointyz.m_coordinates(1)==pointxz.m_coordinates(1))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose Z-Coordinate do not match";
			return;
		}
		else{
			m_coordinates(0) = pointxz.m_coordinates(0);
			m_coordinates(1) = pointyz.m_coordinates(0);
			m_coordinates(2) = pointyz.m_coordinates(1);
		}
		
		m_index = pointyz.m_index;
		return;
	}

	// regenerates the point given 2 projections: XY and XZ
	void regenerate2_XY_XZ(Point2 &pointxy, Point2 &pointxz){
		if(m_index!=-1){
			cout<<"\nWARNING : Overwriting an aldready existing Point.";
			return;
		}
			
		if(!(pointxy.m_OnXY && pointxz.m_OnXZ)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points which are not on XY, YZ plane.";
			return;
		}
		
		if(!(pointxy.m_index == pointxz.m_index)){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose indexes does not match";
			return;
		}
		
		if(!(pointxy.m_coordinates(0)==pointxz.m_coordinates(0))){
			cout<<"\nWARNING : ReGenerating a 3D Point from 2D Points whose X-Coordinate do not match";
			return;
		}
		else{
			m_coordinates(0) = pointxy.m_coordinates(0);
			m_coordinates(1) = pointxy.m_coordinates(1);
			m_coordinates(2) = pointxz.m_coordinates(1);
		}
		
		m_index = pointxy.m_index;
		return;
	}

	// regenerates a point given 2 projection
	void regenerate2(Point2 &point1, Point2 &point2){
		if(point1.m_OnXY && point2.m_OnYZ){
			regenerate2_XY_YZ(point1, point2);
		}
		else if(point1.m_OnYZ && point2.m_OnXY){
			regenerate2_XY_YZ(point2, point1);
		}
		else if(point1.m_OnYZ && point2.m_OnXZ){
			regenerate2_YZ_XZ(point1, point2);
		}
		else if(point1.m_OnXZ && point2.m_OnYZ){
			regenerate2_YZ_XZ(point2, point1);
		}
		else if(point1.m_OnXY && point2.m_OnXZ){
			regenerate2_XY_XZ(point1, point2);
		}
		else if(point1.m_OnXZ && point2.m_OnXY){
			regenerate2_XY_XZ(point2, point1);
		}
		else{
			cout<<"\nWARNING : ReGenerating a 3D point from 2D Points o the same plane";
			return;
		}
	}

	// Rotate a point around a Line ----------- Ref: http://paulbourke.net/geometry/rotate/
	// Angle in Radian between 0.0 to 360.0
	Point3 rotate(Line &line, double angle){
		
		if(m_index==-1){
			cout<<"\nWAARNING: Empty Point, Can't Rotate.";
			return Point3();
		}
		
		double t = (angle * PI/180);
		
		double x = line.m_intercept(0); 
		double y = line.m_intercept(1); 
		double z = line.m_intercept(2);
		
		double a = line.m_directionCosine(0);
		double b = line.m_directionCosine(1);
		double c = line.m_directionCosine(2); 
		
		Matrix4f T;
		T<< 1.0, 0.0, 0.0, -x,
			0.0, 1.0, 0.0, -y,
			0.0, 0.0, 1.0, -z,
			0.0, 0.0, 0.0, 1.0;
			
		Matrix4f T_inv;
		T_inv<< 1.0, 0.0, 0.0, x,
				0.0, 1.0, 0.0, y,
				0.0, 0.0, 1.0, z,
				0.0, 0.0, 0.0, 1.0;
			
		double mag = sqrt(a*a + b*b + c*c);
		a = a/mag;
		b = b/mag;
		c = c/mag;
		double d = sqrt(b*b + c*c);
		
		Matrix4f Rx;
		Matrix4f Rx_inv;
		
		if(d!=0){
		
			Rx<< 1.0, 0.0, 0.0, 0.0,
				 0.0, (c/d), (-b/d), 0.0,
				 0.0, (b/d), (c/d), 0.0,
				 0.0, 0.0, 0.0, 1.0;
			
			Rx_inv<< 1.0, 0.0, 0.0, 0.0,
				 	 0.0, (c/d), (b/d), 0.0,
				 	 0.0, (-b/d), (c/d), 0.0,
				 	 0.0, 0.0, 0.0, 1.0; 
		}
		
		Matrix4f Ry;
		Ry<< d, 0.0, -a, 0.0,
			 0.0, 1.0, 0.0, 0.0,
			 a, 0.0, d, 0.0,
			 0.0, 0.0, 0.0, 1.0;
			 
		Matrix4f Ry_inv;
		Ry_inv<< d, 0.0, a, 0.0,
			 	 0.0, 1.0, 0.0, 0.0,
			 	 -a, 0.0, d, 0.0,
			 	 0.0, 0.0, 0.0, 1.0;
		
		Matrix4f Rz;
		Rz<< cos(t), -sin(t), 0.0, 0.0,
			 sin(t), cos(t), 0.0, 0.0,
			 0.0, 0.0, 1.0, 0.0,
			 0.0, 0.0, 0.0, 1.0;
			 
		Vector4f new_coordinates;
		Vector4f old_coordinates;
		
		old_coordinates<< m_coordinates(0), m_coordinates(1), m_coordinates(2), 1.0; 
			 
		if(d==0){
			new_coordinates = T_inv * Ry_inv * Rz * Ry * T * old_coordinates;
		}
		else{
			new_coordinates = T_inv * Rx_inv * Ry_inv * Rz * Ry * Rx * T * old_coordinates;
		}
		
		return Point3(new_coordinates(0), new_coordinates(1), new_coordinates(2), m_index);
	}
	
	Point3 rotateX(double angle){
		double t = (angle * PI/180);

		double x = m_coordinates(0);
		double y = m_coordinates(1);
		double z = m_coordinates(2);

		double new_y = y*cos(t) - z*sin(t);
		double new_z = y*sin(t) + z*cos(t);
	
		return Point3(x, new_y, new_z, m_index);
	}

	Point3 rotateY(double angle){
		double t = (angle * PI/180);

		double x = m_coordinates(0);
		double y = m_coordinates(1);
		double z = m_coordinates(2);

		double new_x = x*cos(t) + z*sin(t);
		double new_z = z*cos(t) - x*sin(t);
	
		return Point3(new_x, y, new_z, m_index);
	}

	Point3 rotateZ(double angle){
		double t = (angle * PI/180);

		double x = m_coordinates(0);
		double y = m_coordinates(1);
		double z = m_coordinates(2);

		double new_x = x*cos(t) - y*sin(t);
		double new_y = x*sin(t) + y*cos(t);
	
		return Point3(new_x, new_y, z, m_index);
	}

	// print the point in the format "P1 : (3.0, 4.0, 5.0)"
	void print(){
		cout<<"\nP"<< m_index<<" : ("<<m_coordinates(0)<<", "<<m_coordinates(1)<<", "<<m_coordinates(2)<<")";
		return;
	}
	
	// returns true if both the Points coiincide
	bool isSame(Point3 &point){
		return (point.m_coordinates(0) == m_coordinates(0)) && (point.m_coordinates(1) == m_coordinates(1)) 
				&& (point.m_coordinates(2) == m_coordinates(2));
	}

};

#endif
