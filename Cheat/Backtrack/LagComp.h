#pragma once
#include "../../Engine/Engine.h"

#define PI 3.14159265358979323846f
#define MAXBACKTRACKTICKS ((int)Settings::Aimbot::aim_Backtracktime)
#define TICK_INTERVAL	(Interfaces::GlobalVars()->interval_per_tick)
#define TIME_TO_TICKS( dt )	( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

inline Vector angle_vector(Vector past)
{
	auto sy = sin(past.y / 180.f * static_cast<float>(PI));
	auto cy = cos(past.y / 180.f * static_cast<float>(PI));

	auto sp = sin(past.x / 180.f * static_cast<float>(PI));
	auto cp = cos(past.x / 180.f* static_cast<float>(PI));

	return Vector(cp*cy, cp*sy, -sp);
}
inline float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}

namespace SDK
{
	struct lbyRecords
	{
		int tick_count;
		float lby;
		Vector headPosition;
	};

	struct backtrackData
	{
		float simtime;
		Vector hitboxPos;
	};

	class BackTrack
	{
		int latest_tick;
		bool IsTickValid(int tick);
		void UpdateRecord(int i);
	public:
		lbyRecords records[64];
		bool RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint);
		void legitBackTrack(CUserCmd * cmd);
		void Update(int tick_count);
	};
}

extern backtrackData headPositions[64][25]; //same

extern BackTrack* backtracking;

int BacktrackTicks();