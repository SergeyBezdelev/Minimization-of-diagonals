#include "Functional.h"

void findIndexes(int n, int cutsRem, Point* points, int* indexBuff, int index, double* minPrice, int* bestBuffer) {
	// ‘инальный шаг функции
	if (cutsRem == 0) {
		double price = 0; // »нициализаци€ переменной дл€ подсчета стоимости рекурсивно сформированного буфера
		//÷икл дл€ всех разрезов
		for (int i = 0; i < n - 3; i++) {
			// i1 и i2 определ€ют индексы углов между которыми будет проведена лини€
			int i1 = indexBuff[i] - 1;
			int i2 = indexBuff[i] + 1;

			// »значально это соседние углы, но если соседний угол уже отрезан, нужно двигатьс€ дальше до первого неотрезанного угла
			while (true) {
				// проверка, обеспечивающа€ цикличность индексов (ѕосле (n - 1)-го индекса снова идет 0-ой и наоборот)
				if (i1 < 0) i1 = n - 1;
				if (i2 == n) i2 = 0;

				bool i1found = false, i2found = false; // ѕроверка, что i1 и i2 не отрезаны
				for (int j = 0; j < i; j++) {
					if (i1 == indexBuff[j]) i1found = true;
					if (i2 == indexBuff[j]) i2found = true;
				}

				if (i1found) i1--; // ≈сли один из них был отрезан, то он сдвигаетс€ на следующую позицию
				if (i2found) i2++;
				if (!(i1found || i2found)) break; // ≈сли оба не отрезаны, выход из цикла
			}

			double dx = points[i2].x - points[i1].x; // –асчет стоимости линии и добавление к общей стоимости
			double dy = points[i2].y - points[i1].y;
			price += sqrt(dx * dx + dy * dy);
		}
		if (price < *minPrice) { // ≈сли стоимость меньше минимальной, обновл€ем минимальную стоимость и заносим результаты в bestBuffer
			*minPrice = price;
			for (int i = 0; i < n - 3; i++) {
				bestBuffer[i] = indexBuff[i];
			}
		}
		return;
	}
	//ѕри каждом рекурсивном вызове indexBuffer дополн€етс€ 1-ым индексом, которого еще не было (мы не можем 2-жды отрезать 1 угол)
	for (int i = 0; i < n; i++) {
		bool alreadyUsed = false; // ѕроверка, что индекс еще не записан
		for (int j = 0; j < n - 3; j++) {
			if (i == indexBuff[j]) alreadyUsed = true;
		}
		if (alreadyUsed) continue;
		int* newIndexBuff = new int[n - 3]; // —оздание нового буфера и занесение туда нужных цифр
		for (int i = 0; i < n - 3; i++) {
			newIndexBuff[i] = indexBuff[i];
		}
		newIndexBuff[index] = i;
		int newIndex = index + 1;

		// —ледующий рекурсивный вызов
		findIndexes(n, cutsRem - 1, points, newIndexBuff, newIndex, minPrice, bestBuffer);
	}
}
//провести линию
void DrawLine(sf::RenderWindow* window, double x1, double y1, double x2, double y2) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	double longness = sqrt(dx * dx + dy * dy);
	double thickness = 5;

	sf::RectangleShape rect(sf::Vector2f(longness, thickness)); //создаетс€ пр€моугольник, который будет представл€ть линию
	rect.setFillColor(sf::Color(100, 0, 0));
	rect.setOrigin(0, 1.5);
	rect.setRotation(atan(dy / dx) * 180 / 3.1415);
	if (x1 < x2) {
		rect.setPosition(sf::Vector2f(x1, y1));
	} else if (x1 == x2) {
		rect.setRotation(abs(atan(dy / dx) * 180 / 3.1415));
		if (y1 < y2) {
			rect.setPosition(sf::Vector2f(x1, y1));
		} else {
			rect.setPosition(sf::Vector2f(x2, y2));
		}
	} else {
		rect.setPosition(sf::Vector2f(x2, y2));
	}
	window->draw(rect);
}