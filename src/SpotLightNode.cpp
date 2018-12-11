#include "SpotLightNode.h"

SpotLightNode::SpotLightNode(SpotLight * light, Mesh * mesh, GraphNode * parent) : light(light), GraphNode(mesh, parent) {
	rotationZ = 0.0f;
	rotationY = 0.0f;
	appliedZ = 0.0f;
	appliedY = 0.0f;
	pos = light->position;
	constant = light->constant;
	linear = light->linear;
	quadratic = light->quadratic;
	cutOff = light->cutOff;
	outerCutOff = light->outerCutOff;
	lastEnabled = true;
}

void SpotLightNode::update(double timeDiff) {
	light->model = getWorld();
	GraphNode::update(timeDiff);
}

void SpotLightNode::drawGui(bool autoUpdate) {
	ImGui::Checkbox("SpotLight enabled", &lastEnabled);
	ImGui::NewLine();
	if (lastEnabled) {
		ImGui::SliderAngle("SpotLight rotationZ", &rotationZ);
		ImGui::NewLine();
		ImGui::SliderAngle("SpotLight rotationY", &rotationY);
		ImGui::NewLine();
		ImGui::SliderFloat3("SpotLight position", (float*)&pos, -10.0f, 10.0f);
		ImGui::NewLine();
		ImGui::SliderFloat("SpotLight constant", &constant, 0.0f, 10.0f);
		ImGui::NewLine();
		ImGui::SliderFloat("SpotLight linear", &linear, 0.0f, 10.0f);
		ImGui::NewLine();
		ImGui::SliderFloat("SpotLight quadratic", &quadratic, 0.0f, 10.0f);
		ImGui::NewLine();
		ImGui::SliderFloat("SpotLight cutOff", &cutOff, 0.0f, 10.0f);
		ImGui::NewLine();
		ImGui::SliderFloat("SpotLight outerCutOff", &outerCutOff, cutOff, 10.0f);
		ImGui::NewLine();
		ImGui::ColorEdit3("SpotLight color", (float*)&(light->diffuse));
		ImGui::NewLine();
	}

	if (autoUpdate || ImGui::Button("Apply SpotLight changes")) {
		light->position = pos;
		light->constant = constant;
		light->linear = linear;
		light->quadratic = quadratic;
		light->cutOff = cutOff;
		light->outerCutOff = outerCutOff;
		local = glm::translate(glm::mat4(1.0f), glm::vec3(light->position));
		if (rotationZ != appliedZ || rotationY != appliedY) {
			appliedZ = rotationZ;
			appliedY = rotationY;
			local = glm::rotate(local, rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
			local = glm::rotate(local, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		dirty = true;
		light->model = getWorld();
		if (lastEnabled != enabled) {
			enabled = lastEnabled;
			if (enabled) {
				light->ambient = lastAmbient;
				light->diffuse = lastDiffuse;
				light->specular = lastSpecular;
			} else {
				lastAmbient = light->ambient;
				lastDiffuse = light->diffuse;
				lastSpecular = light->specular;
				light->ambient = glm::vec4(0.0f);
				light->diffuse = glm::vec4(0.0f);
				light->specular = glm::vec4(0.0f);
			}
		}
	}
}

SpotLight * SpotLightNode::getLight() {
	return light;
}
