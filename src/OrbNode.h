#ifndef ORBNODE_H
#define ORBNODE_H

#include "GraphNode.h"
#include "MeshSphere.h"
#include "BlockNode.h"
#include "MeshColorSphere.h"
#include "MeshRefSphere.h"

class OrbNode : public GraphNode {
public:
	OrbNode(MeshSphere* mesh, float speed, glm::vec2 direction, GraphNode* parent = nullptr);
	OrbNode(MeshColorSphere* mesh, float speed, glm::vec2 direction, GraphNode* parent = nullptr);
	OrbNode(MeshRefSphere* mesh, float speed, glm::vec2 direction, GraphNode* parent = nullptr);
	void update(double timeDiff) override;
	bool tryCollide(BlockNode *block);
	glm::vec2 getDirection();
	glm::vec3 actualCenter();
	float getRadius();
	float speed;
protected:
	void bounce(CollisionState state);
	glm::vec2 direction;
	float radius;
};

#endif
