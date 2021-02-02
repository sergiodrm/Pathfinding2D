#pragma once

#include "Engine/DrawUtilities/Grid.h"
#include "Utils.h"
#include "Node.h"
#include <vector>

namespace Pathfinding
{
	class CWorldGenerator
	{

	public:

		CWorldGenerator(const Vec2& _worldSize);

		void SetOrigin(const Vec2& _origin);
		void SetDestiny(const Vec2& _destiny);
		void SetHeuristic(HeuristicFunction _pFunction);

		void Update();

	private:

		std::vector<CNode*>::iterator GetLessScoreNode();
		void UpdateGrid();
		bool UpdateCurrentNode(CNode* _pCurrentNode);
		uint GetIndexNode(CNode* _pNode) const;

	private:

		CGrid m_grid;
		Vec2 m_origin;
		Vec2 m_destiny;
		HeuristicFunction m_pHeuristicFunction;
		std::vector<CNode*> m_openNodes;
		std::vector<CNode*> m_closedNodes;
	};
}
