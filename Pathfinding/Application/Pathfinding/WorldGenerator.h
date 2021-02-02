#pragma once

#include "Engine/DrawUtilities/Grid.h"
#include "Utils.h"
#include "Node.h"
#include <vector>

namespace Pathfinding
{
	struct SColor
	{
		float m_tColor[4];
	};
	class CWorldGenerator
	{

	public:

		CWorldGenerator(const Vec2& _worldSize);

		void SetOrigin(const Vec2& _origin);
		void SetDestiny(const Vec2& _destiny);
		void SetHeuristic(HeuristicFunction _pFunction);

		void Init(const Vec2& _origin, const Vec2& _destiny);
		void PathfindingSlot();

	private:

		std::vector<CNode*>::iterator GetLessScoreNode();
		void UpdateGrid(const Vec2& _currentPosition);
		bool CheckGoalAchieved(CNode* _pCurrentNode) const;
		bool CheckCollision(const Vec2& _coordenates) const;
		CNode* FindNode(std::vector<CNode*>& _container, const Vec2& _coordenates) const;
		void MakePath(CNode* _pGoal);
		SColor GetColor(const Vec2& _coordenates, bool _bInOpenList = true);
	private:

		CGrid m_grid;
		Vec2 m_origin;
		Vec2 m_destiny;
		HeuristicFunction m_pHeuristicFunction;
		std::vector<CNode*> m_openNodes;
		std::vector<CNode*> m_closedNodes;
		bool m_bPathFound;
	};
}
