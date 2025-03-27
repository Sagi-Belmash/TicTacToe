//
// Created by sagib on 23/01/2025.
//
#ifndef TICTACTOE_MAIN_H
#define TICTACTOE_MAIN_H


#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Game.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void	mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void	createO(VBO& symbolVBO, float x, float y);
void	createX(VBO& symbolVBO, float x, float y);
void	refreshWindow(GLFWwindow* window, VAO gridVAO, EBO gridEBOs[3], VAO symbolVAOs[9], VAO winVAO);
void	handlePlayerMove(Game& game, VAO symbolVAOs[9], VBO symbolVBOs[9], int& turn);

#endif //TICTACTOE_MAIN_H

