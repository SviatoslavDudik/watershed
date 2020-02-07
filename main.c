#include "image.h"
#include "watershed.h"

int main() {
	myimage img, grad;
	img = LireImage("test.png");
	EcrireImage(img, "test2.png");
	grad = CalculerGradient(img, 1);
	EcrireImage(grad, "Gradient1.png");
	LibererImage(grad);
	grad = CalculerGradient(img, 5);
	EcrireImage(grad, "Gradient5.png");
	LibererImage(grad);
	grad = CalculerGradient(img, 10);
	EcrireImage(grad, "Gradient10.png");
	LibererImage(grad);
	LibererImage(img);
	return 0;
}
