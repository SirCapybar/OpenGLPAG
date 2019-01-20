#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UiElement.h"
#include <functional>

enum UiButtonState {
	Idle,
	Hover,
	Clicked
};


class UiButton : public UiElement {
public:
	UiButton(Shader *shader, char* textureIdle, char* textureHover, char* textureClicked, glm::vec2 position, glm::vec2 size, bool center = true);
	void render() override;
	void mouse_callback(GLFWwindow* window, double xpos, double ypos) override;
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
	void setButtonCallback(std::function<void()> callback);
	UiButtonState getState();
protected:
	Texture textureHover, textureClicked;
	UiButtonState state = Idle;
	bool clicked = false, hover = false;
	std::function<void()> callback = [](){};
};

#endif