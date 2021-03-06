#pragma once

#include "Engine/DrawUtilities/Grid.h"
#include "Utils.h"
#include <vector>
#include "Node.h"

namespace Pathfinding
{
	struct SColor
	{
		float m_tColor[4];
	};

	class CPathSolver
	{
	public:

		CPathSolver(const Vec2& _worldSize);

		void SetOrigin(const Vec2& _origin);
		void SetDestiny(const Vec2& _destiny);
		void SetHeuristic(HeuristicFunction _pFunction);

		void Init(const Vec2& _origin, const Vec2& _destiny);
		void PathfindingSlot();

	private:
		CNode* GetNextPathNode();
		void UpdateLists();
		void UpdateGrid(const Vec2& _currentPosition);
		bool CheckGoalAchieved(CNode* _pCurrentNode) const;
		bool CheckCollision(const Vec2& _coordenates) const;
		void MakePath(CNode* _pGoal);
		SColor GetColor(const Vec2& _coordenates, bool _bInOpenList = true) const;
		void CreateNode(CNode* _pParent, const Vec2& _coordenates);

		static void SortVector(std::vector<CNode*>& _vector_);
    static CNode* FindNode(std::vector<CNode*>& _container, const Vec2& _coordenates);
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
