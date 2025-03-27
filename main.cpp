//
// Created by sagib on 21/01/2025.
//
#include "Main.h"
#include "Game.h"
#include "shaderClass.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>

#define GAME_START "==============================\n=====     GAME START     =====\n==============================\n"
#define WINDOW_W 1000
#define WINDOW_H 1000
#define LEN 0.5f
#define C_VERTICES 60
#define R 0.1f
#define COOLDOWN 1.5

double mouseX, mouseY;
bool playerPlayed = false;
bool validMove = true;
double cooldownTime = -COOLDOWN;


int main() {
	// Initializing GLFW
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	// Creating GLFW window
	GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "TicTacToe", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	// Initializing glad
	gladLoadGL();
	glViewport(0, 0, WINDOW_W, WINDOW_H);

	// Grid vertices and indices
	GLfloat gridVertices[] = {
		-LEN,		LEN,		0.0f, // Upper left = 0
		-LEN / 3,	LEN,		0.0f, // Upper left 1/3 = 1
		LEN / 3,	LEN,		0.0f, // Upper right 1/3 = 2
		LEN,		LEN,		0.0f, // Upper right = 3
		LEN,		LEN / 3,	0.0f, // 1/3 upper right = 4
		LEN,		-LEN / 3,	0.0f, // 1/3 lower right = 5
		LEN,		-LEN,		0.0f, // Lower right = 6
		LEN / 3,	-LEN,		0.0f, // Lower right 1/3 = 7
		-LEN / 3,	-LEN,		0.0f, // Lower left 1/3 = 8
		-LEN,		-LEN,		0.0f, // Lower left = 9
		-LEN,		-LEN / 3,	0.0f, // 1/3 lower left = 10
		-LEN,		LEN / 3,	0.0f, // 1/3 upper left = 11
	};
	GLuint gridIndices1[] = { 1, 2, 7, 8 }; // Vertical center rectangle
	GLuint gridIndices2[] = { 4, 5, 10, 11 }; // Horizontal center rectangle
	GLuint gridIndices3[] = { 0, 3, 6, 9 }; // Whole square 

	// Grid and symbols's VAO, VBO, EBO, Shader program
	Shader shaderProgram("grid.vert", "grid.frag");
	VAO gridVAO;
	VBO gridVBO(gridVertices, sizeof(gridVertices));
	EBO gridEBO1(gridIndices1, sizeof(gridIndices1));
	EBO gridEBO2(gridIndices2, sizeof(gridIndices2));
	EBO gridEBO3(gridIndices3, sizeof(gridIndices3));
	EBO gridEBOs[] = { gridEBO1, gridEBO2, gridEBO3 };

	VAO symbolVAOs[9];
	VBO symbolVBOs[9];
	gridVAO.Bind();
	gridVAO.LinkAttrib(gridVBO, 0, 3, GL_FLOAT, 0, (void*)0);

	// Win vertices, VAO, VBO;
	GLfloat winVertices[6] = { 0 };
	VAO winVAO;
	VBO winVBO;

	// Setting the window
	shaderProgram.Activate();

	// Running the game
	Game& game = Game::getInstance();
	int begin, end;
	float coordinates[] = { -LEN * 2 / 3, 0, LEN * 2 / 3 };
	float winTail[] = { -0.1f, 0, 0.1f };
	int turn = 0;
	while (!glfwWindowShouldClose(window)) {
		refreshWindow(window, gridVAO, gridEBOs, symbolVAOs, winVAO);

		// Make move
		if (playerPlayed) {
			handlePlayerMove(game, symbolVAOs, symbolVBOs, turn);
			// Swap players if there is no winner yet
			if (!game.checkWin(&begin, &end)) {
				if (turn >= 9) {
					cooldownTime = glfwGetTime();
				}
				else if (validMove) {
					game.switchPlayer();
				}
			}
			// If there is a winner start the win cooldown and generate the win line
			else {
				cooldownTime = glfwGetTime();
				winVertices[0] = begin % 3 - end % 3  == 0 ? coordinates[begin % 3] : coordinates[begin % 3] + winTail[begin % 3];
				winVertices[1] = begin / 3 - end / 3 == 0 ? -coordinates[begin / 3] : -coordinates[begin / 3] - winTail[begin / 3];
				winVertices[3] = begin % 3 - end % 3 == 0 ? coordinates[end % 3] : coordinates[end % 3] + winTail[end % 3];
				winVertices[4] = begin / 3 - end / 3 == 0 ? -coordinates[end / 3] : -coordinates[end / 3] - winTail[end / 3];
				winVAO.Bind();
				winVBO.Update(winVertices, sizeof(winVertices));
				winVAO.LinkAttrib(winVBO, 0, 3, GL_FLOAT, 0, (void*)0);
			}
		}

		// After the cooldown reset everything
		if ((game.checkWin(&begin, &end) || turn >= 9) && glfwGetTime() - cooldownTime > COOLDOWN) {
			game.resetGame();
			for (int i = 0; i < 9; i++) {
				symbolVBOs[i].Update(0, 0);
				symbolVAOs[i].Bind();
				symbolVAOs[i].LinkAttrib(symbolVBOs[i], 0, 3, GL_FLOAT, 0, (void*)0);
			}
			for (float& vertix : winVertices) {
				vertix = 0;
			}
			winVBO.Update(0, 0);
			winVAO.Bind();
			winVAO.LinkAttrib(winVBO, 0, 3, GL_FLOAT, 0, (void*)0);
			turn = 0;
		}
		
	}
	// Deleting everything before exiting
	shaderProgram.Delete();
	gridVAO.Delete();
	gridVBO.Delete();
	for (EBO gridEBO : gridEBOs) { gridEBO.Delete(); }
	for (VAO symbolVAO : symbolVAOs) { symbolVAO.Delete(); }
	for (VBO symbolVBO : symbolVBOs) { symbolVBO.Delete(); }
	winVAO.Delete();
	winVBO.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Bye bye!" << std::endl;
	return 0;
}

void refreshWindow(GLFWwindow* window, VAO gridVAO, EBO gridEBOs[3], VAO symbolVAOs[9], VAO winVAO) {
	// Drawing settings
	glLineWidth(10);
	glPointSize(10);
	// Drawing the grid
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gridVAO.Bind();
	for (int i = 0; i < 3; i++) {
		gridEBOs[i].Bind();
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	}
	glDrawElements(GL_POINTS, 4, GL_UNSIGNED_INT, 0);

	// Drawing the symbols
	for (int i = 0; i < 9; i++) {
		symbolVAOs[i].Bind();
		glDrawArrays(GL_LINES, 0, C_VERTICES);
	}
	
	// Drawing the win line
	glLineWidth(20);
	winVAO.Bind();
	glDrawArrays(GL_LINES, 0, 2);

	// Updating window
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (glfwGetTime() - cooldownTime > COOLDOWN &&  button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		// Convert to OpenGL coordinates
		if (!playerPlayed) {
			mouseX = (2.0f * xPos) / WINDOW_W - 1.0f;
			mouseY = 1.0f - (2.0f * yPos) / WINDOW_H;
			playerPlayed = true;
		}
	}
}

void createO(VBO& symbolVBO, float x, float y) {
	GLfloat vertices[C_VERTICES * 3];
	GLfloat vx, vy;
	for (int i = 0; i < C_VERTICES * 3; i += 3) {
		vx = x + R * float(cos(i * 2.0f * M_PI / C_VERTICES));
		vy = y + R * float(sin(i * 2.0f * M_PI / C_VERTICES));
		vertices[i] = vx;
		vertices[i + 1] = vy;
		vertices[i + 2] = 0;
	}
	symbolVBO.Update(vertices, sizeof(vertices));
}

void createX(VBO& symbolVBO, float x, float y) {
	GLfloat vertices[] = {
		x + R, y + R, 0.0f,
		x - R, y - R, 0.0f,
		x + R, y - R, 0.0f,
		x - R, y + R, 0.0f,
	};
	
	symbolVBO.Update(vertices, sizeof(vertices));
}

void handlePlayerMove(Game& game, VAO symbolVAOs[9], VBO symbolVBOs[9], int& turn) {
	int row, col;
	float coordinates[] = { -LEN * 2 / 3, 0, LEN * 2 / 3 };

	// The col coordinate
	if (mouseX > -LEN && mouseX < -LEN / 3) {
		col = 0;
	}
	else if (mouseX > -LEN / 3 && mouseX < LEN / 3) {
		col = 1;
	}
	else if (mouseX > LEN / 3 && mouseX < LEN) {
		col = 2;
	}
	else {
		col = -1;
	}

	// The row coordinates
	if (mouseY > -LEN && mouseY < -LEN / 3) {
		row = 2;
	}
	else if (mouseY > -LEN / 3 && mouseY < LEN / 3) {
		row = 1;
	}
	else if (mouseY > LEN / 3 && mouseY < LEN) {
		row = 0;
	}
	else {
		row = -1;
	}

	validMove = game.makeMove(row, col);
	if (validMove) {
		if (game.getCurrentPlayer() == 'X') {
			createX(symbolVBOs[turn], coordinates[col], -coordinates[row]);
		}
		else {
			createO(symbolVBOs[turn], coordinates[col], -coordinates[row]);
		}
		symbolVAOs[turn].Bind();
		symbolVAOs[turn].LinkAttrib(symbolVBOs[turn], 0, 3, GL_FLOAT, 0, (void*)0);
		turn++;
	}
	std::cout << "Coordinates: ( " << row << " , " << col << " )\nValid move: " << validMove << std::endl;
	playerPlayed = false;
}