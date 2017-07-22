#pragma once
#ifndef _V_KDIMENSIONALTREE_H_
#define _V_KDIMENSIONALTREE_H_

#include "../../Structure/Distance/VDistance.h"
#include "../MaxHeap/VMaxHeap.h"
#include <vector>
#include <stack>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VKDimensionalTree
    //----------------------------------------------------------------------------------------------------
    template<typename _T>
    class VKDimensionalTree
    {
    protected:
        // Node
        //----------------------------------------------------------------------------------------------------
        struct Node
        {
        public:
            //----------------------------------------------------------------------------------------------------
            inline Node()
                :
                point(),
                depth(0),
                splitDimension(0),
                left(nullptr),
                right(nullptr)
            {
            }
            
            inline Node(unsigned _depth)
                :
                point(),
                depth(_depth),
                splitDimension(0),
                left(nullptr),
                right(nullptr)
            {
            }
            
            //----------------------------------------------------------------------------------------------------
            inline virtual ~Node()
            {
            }
            
        public:
            //----------------------------------------------------------------------------------------------------
            _T point;
            unsigned depth;
            unsigned splitDimension;
            Node *left;
            Node *right;
        };
        
    public:
        //----------------------------------------------------------------------------------------------------
        VKDimensionalTree()
            :
            mRoot(nullptr)
        {
            
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VKDimensionalTree()
        {
            Clear();
        }
        
        //----------------------------------------------------------------------------------------------------
        void Clear()
        {
            if (mRoot)
            {
                Delete(mRoot);
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        bool BuildTree(const std::vector<_T>& _points, unsigned _k)
        {
            Clear();
            if (!_points.size())
            {
                return false;
            }
            
            std::stack<std::pair<Node*, std::vector<_T>>> spaces;
            spaces.push(std::pair<Node*, std::vector<_T>>(mRoot = CreateNode(), _points));
            while (!spaces.empty())
            {
                // Prepare
                std::pair<Node*, std::vector<_T>>& space = spaces.top();
                Node* node = space.first;
                std::vector<_T> nodePoints(std::move(space.second));
                spaces.pop();
                if (nodePoints.size() <= 0)
                {
                    continue;
                }
                else if (nodePoints.size() == 1)
                {
                    node->point = nodePoints[0];
                    continue;
                }
                // Find split dimension (Todo: use variance)
                node->splitDimension = node->depth % _k;
                // Split
                std::sort(nodePoints.begin(), nodePoints.end(), [demension=node->splitDimension](const _T& _first, const _T& _second){ return _first[demension] < _second[demension]; });
                unsigned long middle = nodePoints.size() / 2;
                node->point = nodePoints[middle];
                std::vector<_T> rightPoints;
                std::copy(nodePoints.begin() + middle + 1, nodePoints.end(), std::back_inserter(rightPoints));
                nodePoints.resize(middle);
                if (nodePoints.size())
                {
                    spaces.push(std::pair<Node*, std::vector<_T>>(node->left = CreateNode(node->depth + 1), std::move(nodePoints)));
                }
                if (rightPoints.size())
                {
                    spaces.push(std::pair<Node*, std::vector<_T>>(node->right = CreateNode(node->depth + 1), std::move(rightPoints)));
                }
            }
            
            return false;
        }
        
        //----------------------------------------------------------------------------------------------------
        std::vector<_T> Search(const _T& _point, unsigned int _maxCount)
        {
            VMaxHeap<double, _T> heap;
            Search(mRoot, _point, _maxCount, heap);
            std::vector<_T> result;
            while (heap.Size())
            {
                result.push_back(heap.Front());
                heap.PopFront();
            }
            return result;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        inline virtual Node* CreateNode(unsigned _depth=0)
        {
            return new Node(_depth);
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Search(Node* _node, const _T& _point, unsigned int _maxCount, VMaxHeap<double, _T>& _heap)
        {
            if (_node)
            {
                // Find leaf
                Node *child = nullptr;
                if (_node->left == nullptr)
                {
                    child = _node->left;
                }
                else if (_node->right == nullptr)
                {
                    child = _node->right;
                }
                else
                {
                    child = _point[_node->splitDimension] < _node->point[_node->splitDimension] ? _node->left : _node->right;
                }
                Search(child, _point, _maxCount, _heap);
                // Calculate point distance
                double distance = VDistance<_T, VDistanceType::Euclidean>::Calculate(_point, _node->point);
                if (_heap.Size() < _maxCount)
                {
                    _heap.Insert(distance, _node->point);
                }
                else if (_heap.Size() && distance < _heap.FrontKey())
                {
                    _heap.Insert(distance, _node->point);
                    _heap.PopFront();
                }
                // Calculate the distance between point and hyperplane && Find another branch
                double hyperplaneDistance = std::abs(_point[_node->splitDimension] - _node->point[_node->splitDimension]);
                if (_heap.Size() < _maxCount || hyperplaneDistance < _heap.FrontKey())
                {
                    Search(child == _node->left ? _node->right : _node->left, _point, _maxCount, _heap);
                }
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Delete(Node*& _node)
        {
            if (_node)
            {
                // Delete children
                Delete(_node->left);
                Delete(_node->right);
                // Delete self
                delete _node;
                _node = nullptr;
            }
        }
        
        //----------------------------------------------------------------------------------------------------

        
    protected:
        //----------------------------------------------------------------------------------------------------
        Node* mRoot;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VKDimensionalTreeTest();
}

#endif
