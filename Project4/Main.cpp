/* ��� �������� n - ��������(�������� ������������ ����� ������ � ������� ������).
��� ��������� �� ������������ (n � 3) �����������. ���������� ���������� ������
����� ���� ���� �������������� ����������. ����� ����������� ��������� ����������. */
using namespace std;
#include "Functional.h"

int main(void) {
	setlocale(LC_ALL, "rus");

	// ���� ���������� ����� � ��������� �� ������
	int n = 0;
	while (n <= 3) {
		cout << "������� ���������� ����� (>3): ";
		cin >> n;
		if (cin.fail()) {
			cin.clear();
			char skippingChar;
			while (cin.get(skippingChar) && (skippingChar != '\n') && (skippingChar != ' '));
		}
	}

	// ���� �����
	Point* points = new Point[n];
	for (int i = 0; i < n; i++) {
		while (true) {
			cout << "���������� X: ";
			cin >> points[i].x;
			if (cin.fail()) {
				cin.clear();
				char skippingChar;
				while (cin.get(skippingChar) && (skippingChar != '\n') && (skippingChar != ' '));
			}
			else {
				break;
			}
		}
		while (true) {
			cout << "���������� Y: ";
			cin >> points[i].y;
			if (cin.fail()) {
				cin.clear();
				char skippingChar;
				while (cin.get(skippingChar) && (skippingChar != '\n') && (skippingChar != ' '));
			}
			else {
				break;
			}
		}
	}

	// ���������� ������ ������
	double minX = points[0].x, maxX = points[0].x, minY = points[0].y, maxY = points[0].y;
	for (int i = 1; i < n; i++) {
		if (points[i].x > maxX) maxX = points[i].x;
		if (points[i].y > maxY) maxY = points[i].y;
		if (points[i].x < minX) minX = points[i].x;
		if (points[i].y < minY) minY = points[i].y;
	}

	// ����������� ������������ ���������������
	double scaleX = 900 / (maxX - minX);
	double scaleY = 600 / (maxY - minY);
	double scale = min(scaleX, scaleY);

	// ������������� ���������� ��� ������ ����������� �������
	int cuts = n - 3;
	int* indexBuff = new int[cuts];
	for (int i = 0; i < cuts; i++) {
		indexBuff[i] = -1;
	}
	int* bestIndexBuff = new int[cuts];
	double minPrice = ((maxX - minX) + (maxY - minY)) * n;

	// ����� ����������� �������, ��� ���������� ������ ���������� ��������
	findIndexes(n, cuts, points, indexBuff, NULL, &minPrice, bestIndexBuff);
	cout << "����������� ��������� = " << minPrice << "\n";

	// �������� ������� � ��������� ����������� �����
	int* cutsBuff = new int[cuts * 2];
	for (int i = 0; i < cuts; i++) {
		int i1 = bestIndexBuff[i] - 1;
		int i2 = bestIndexBuff[i] + 1;

		while (true) {
			if (i1 < 0) i1 = n - 1;
			if (i2 == n) i2 = 0;

			bool i1found = false, i2found = false;
			for (int j = 0; j < i; j++) {
				if (i1 == bestIndexBuff[j]) i1found = true;
				if (i2 == bestIndexBuff[j]) i2found = true;
			}
			if (i1found) i1--;
			if (i2found) i2++;
			if (!(i1found || i2found)) break;
		}
		cutsBuff[i * 2] = i1;
		cutsBuff[i * 2 + 1] = i2;
	}

	// ������� ����� � �������� ����������
	Point* drawPoints = new Point[n];
	for (int i = 0; i < n; i++) {
		drawPoints[i].x = 50 + (points[i].x - minX) * scale + 450 - 450 / scaleX * scale;
		drawPoints[i].y = 50 + (maxY - points[i].y) * scale + 300 - 300 / scaleY * scale;
	}

	// �������� ���� 
	const int Width = 1000;
	const int Height = 700;
	sf::RenderWindow* window = new sf::RenderWindow();
	window->create(sf::VideoMode(Width, Height), "MultiAngle");
	window->setFramerateLimit(40);

	bool diagReq = 0;

	// ���� ��������� ��������� 
	while (window->isOpen()) {
		window->clear();
		// ��������� ������
		sf::ConvexShape shape;
		shape.setPointCount(n);
		for (int i = 0; i < n; i++) {
			shape.setPoint(i, sf::Vector2f(drawPoints[i].x, drawPoints[i].y));
		}
		shape.setFillColor(sf::Color(0, 100, 0));
		window->draw(shape);

		// ��������� ����������
		if (diagReq) 
			for (int i = 0; i < cuts * 2; i += 2) 
				DrawLine(window, drawPoints[cutsBuff[i]].x, drawPoints[cutsBuff[i]].y,
					drawPoints[cutsBuff[i + 1]].x, drawPoints[cutsBuff[i + 1]].y);
			
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) window->close();
			if (event.type == sf::Event::MouseButtonPressed) diagReq = !diagReq;
		}
		window->display();
	}
}