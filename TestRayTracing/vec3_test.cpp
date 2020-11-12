#include "pch.h"
#include "../RayTracingOneWeekend/vec3.h"
#include "../RayTracingOneWeekend/ray.h"
#include "../RayTracingOneWeekend/sphere.h"
#include "../RayTracingOneWeekend/rtweekend.h"
#include "../RayTracingOneWeekend/hittable_list.h"

TEST(Vec3Class, DeclaringVector)
{
	vec3 v01(5, 8, 6);
	EXPECT_EQ(v01[0], 5);
	EXPECT_EQ(v01[1], 8);
	EXPECT_EQ(v01[2], 6);

	vec3 v02;
	EXPECT_EQ(v02[0], 0);
	EXPECT_EQ(v02[1], 0);
	EXPECT_EQ(v02[2], 0);
}

TEST(Vec3Class, XYZMethods)
{
	vec3 v01(5, 8, 6);
	EXPECT_EQ(v01.x(), 5);
	EXPECT_EQ(v01.y(), 8);
	EXPECT_EQ(v01.z(), 6);
}

TEST(Vec3Class, vec3OperatorOverloads)
{
	// Addition +=
	vec3 v01(6, 8, 10);
	vec3 v02(2, 2, 2);
	vec3 ans01(8, 10, 12);
	EXPECT_EQ(v01 += v02, ans01);


	// Multiplication *=
	vec3 v03(6, 8, 10);
	double scalar01 = 2;
	vec3 ans02(12, 16, 20);
	EXPECT_EQ(v03 *= scalar01, ans02);
	
	// Division /=
	vec3 v04(6, 8, 10);
	double scalar02 = 2;
	vec3 ans03(3, 4, 5);
	EXPECT_EQ(v04 /= scalar02, ans03);

	// unary minus -
	vec3 v05(6, 8, 10);
	vec3 ans04(-6, -8, -10);
	EXPECT_EQ(-(v05), ans04);

	// Substraction -=
	vec3 v06(6, 8, 10);
	vec3 v07(2, 2, 2);
	vec3 ans05(4, 6, 8);
	EXPECT_EQ(v06 -= v07, ans05);
}

TEST(Vec3Class, LengthMethods)
{
	vec3 v01(4, 6, 8);

	EXPECT_EQ(v01.length_squared(), 116);
	EXPECT_EQ(v01.length(), 10.770329614269008062501420983081);
}

TEST(Vec3Class, Vec3Aliases)
{
	point3 p(5, 6, 7);
	color c(5, 6, 7);

	vec3 v(5, 6, 7);

	EXPECT_EQ(p, v); 
	EXPECT_EQ(c, v);
}

TEST(Vec3Class, AdditionOperator)
{
	vec3 v01(2, 4, 6); 
	vec3 v02(1, 2, 3);

	vec3 answ01(3, 6, 9);

	EXPECT_EQ(v01 + v02, answ01);
}

TEST(Vec3Class, SubstractioOperator)
{
	vec3 v01(2, 4, 6);
	vec3 v02(1, 2, 3);

	vec3 answ01(1, 2, 3);

	EXPECT_EQ(v01 - v02, answ01);
}

TEST(Vec3Class, MultiplicationOperator)
{
	vec3 v01(2, 4, 6);
	vec3 v02(1, 2, 3);
	double scalar01 = 2;

	vec3 answ01(2, 8, 18);
	vec3 answ02(4, 8, 12);

	EXPECT_EQ(v01 * v02, answ01);
	EXPECT_EQ(v01 * scalar01, answ02);
	EXPECT_EQ(scalar01 * v01, answ02);
}

TEST(Vec3Class, DivisionOperator)
{
	vec3 v01(2, 4, 6);
	double scalar01 = 2;

	vec3 answ01(1, 2, 3);

	EXPECT_EQ(v01 / scalar01, answ01);
}

TEST(Vec3Class, DotProduct)
{
	vec3 v01(2, 4, 6);
	vec3 v02(1, 2, 3);

	double answ = 28;

	EXPECT_EQ(dot(v01, v02), answ);
}

TEST(Vec3Class, CrossProduct)
{
	vec3 v01(1, 0, 0);
	vec3 v02(0, 1, 0);

	vec3 answ(0, 0, 1);

	EXPECT_EQ(cross(v01, v02), answ);
}

TEST(Vec3Class, UnitVector)
{
	vec3 v01(2, 4, 6);

	EXPECT_EQ(unit_vector(v01).length(), 1.0);
}

TEST(UtilityClass, DoubleEquality)
{
	double d01 = 1.00005; 
	double d02 = 1.00006;
	double d03 = 1.005;

	EXPECT_TRUE(DoubleEquality(d01, d02));
	EXPECT_FALSE(DoubleEquality(d01, d03));

}

TEST(RayClass, RayConstruction)
{
	ray r01; 

	point3 r01_Origin(0, 0, 0);
	vec3 r01_Direction(1, 0, 0); 

	EXPECT_EQ(r01.origin(), r01_Origin);
	EXPECT_EQ(r01.direction(), r01_Direction);

	ray r02(point3(5, 5, 5), vec3(2, 2, 2)); 

	point3 r02_Origin(5, 5, 5);
	vec3 r02_Direction(2, 2, 2);

	EXPECT_EQ(r02.origin(), r02_Origin);
	EXPECT_EQ(r02.direction(), r02_Direction);
}

TEST(RayClass, atMethod)
{
	ray r01; 

	point3 answ (5, 0, 0);

	EXPECT_EQ(r01.at(5), answ);
}

TEST(SphereObject, SphereConstructor)
{
	sphere s01; //unit sphere centered (0,0,0) with radius 1.0

	EXPECT_EQ(s01.center, point3(0, 0, 0));
	EXPECT_EQ(s01.radius, 1.0); 

	sphere s02(point3(1, 1, 1), 0.5); 

	EXPECT_EQ(s02.center, point3(1, 1, 1));
	EXPECT_EQ(s02.radius, 0.5);
}

TEST(SphereObject, SphereHit)
{
	sphere s01; //unit sphere centered (0,0,0) with radius 1.0 
	ray r01(point3(0, 0, -5), vec3(0, 0, 1));
	hit_record hits; 

	s01.hit(r01, -1.0, 10.0, hits);

	EXPECT_EQ(hits.t, 4.0);
	EXPECT_EQ(hits.p, point3(0, 0, -1));
	EXPECT_EQ(hits.normal, vec3(0, 0, -1));
	EXPECT_TRUE(hits.front_face);
}

TEST(SphereObject, RayInsideObjectHit)
{
	sphere s01; //unit sphere centered (0,0,0) with radius 1.0 
	ray r01(point3(0, 0, 0), vec3(0, 0, 1));
	hit_record hits;

	s01.hit(r01, 0.0, 10.0, hits);

	EXPECT_EQ(hits.t, 1.0);
	EXPECT_EQ(hits.p, point3(0, 0, 1));
	EXPECT_EQ(hits.normal, vec3(0, 0, -1));
	EXPECT_FALSE(hits.front_face);

}

TEST(HittableList, ClassMethods) {
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, 0), 1));
	world.add(make_shared<sphere>(point3(0, 0, 3), 1));

	EXPECT_EQ(world.objects.size(), 2); 

	world.clear(); 

	EXPECT_EQ(world.objects.size(), 0);
}

TEST(HittableList, HitMethod) {
	hit_record result;

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, 0), 1));
	world.add(make_shared<sphere>(point3(0, 0, 3), 1));

	ray r01(point3(0, 0, -5), vec3(0, 0, 1)); 

	bool hitAnything = world.hit(r01, 0, infinity, result); 

	EXPECT_TRUE(hitAnything);
	EXPECT_EQ(result.t, 4.0);
	EXPECT_EQ(result.p, point3(0, 0, -1));
	EXPECT_EQ(result.normal, vec3(0, 0, -1));
	EXPECT_TRUE(result.front_face);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}