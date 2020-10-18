#include <bangtal.h>
#include <iostream>
using namespace bangtal;
using namespace std;

class Germ {//세균 오브젝트 클래스
public:
	ObjectPtr virus;
	int x;
	int y;
	Germ() : x(0), y(0) {  };

};

class Heart {
public:
	ObjectPtr heart;
};
int main() {
	auto puzzlebackground = Scene::create("퍼즐", "images/puzzlebackground.png");
	auto conti = Scene::create("", "images/puzzlebackground.png");
	auto party = Object::create("images/party.png", conti, 0, 0);
	auto sad = Object::create("images/");
	int life = 0;
	//퍼즐 오브젝트
	Germ kids[35];
	Germ balls[35];
	Germ puzzle_me;
	Heart hearts[3];
	for (int i = 0; i < 3; i++) {
		hearts[i].heart = Object::create("images/heart.png", puzzlebackground, 100, 100 * (i + 1));
	}

	int left = 272;
	int right = 656;
	int height = 88;
	int row = 7;
	int col = 5;
	int cnt = 0;
	int kid_x = 0;
	int kid_y = 0;

	for (int c = 0; c < col; c++) {
		for (int r = 0; r < row; r++) {
			kid_x = left + 128 * (row - 1 - r);
			kid_y = height + 128 * c;
			balls[cnt].virus = Object::create("images/bubble5.png", puzzlebackground, kid_x, kid_y);
			int who = rand() % 4;
			string kid_name = "images/virus" + to_string(who) + ".png";
			switch (who) {//세균 이미지 랜덤 생성
			case 0:
				kids[cnt].virus = Object::create(kid_name, puzzlebackground, kid_x, kid_y, false);
				break;
			case 1:
				kids[cnt].virus = Object::create(kid_name, puzzlebackground, kid_x, kid_y, false);
				break;
			case 2:
				kids[cnt].virus = Object::create(kid_name, puzzlebackground, kid_x, kid_y, false);
				break;
			case 3:
				kids[cnt].virus = Object::create(kid_name, puzzlebackground, kid_x, kid_y, false);
				break;
			}
			kids[cnt].x = kid_x;
			kids[cnt].y = kid_y;
			cnt++;
		}
	}

	int* random;//세균 개수 동적 할당
	int many;
	cout << "how many viruses do you want to kill?(less than 35): ";
	cin >> many;
	if (many > 35) {
		cout << "less than 35!";
		cout << "how many?(less than 35): ";
		cin >> many;
	}
	random = new int[many];
	for (int i = 0; i < many; i++) {
		random[i] = many + 1;
	}
	int p = 0;
	int path[100][2] = { 0, };
	auto start = Object::create("images/start.png", puzzlebackground, 100, 500);//시작버튼
	auto again = Object::create("images/go-up.png", conti, 100, 100);//시작버튼
	auto end = Object::create("images/stop.png", conti, 700, 150);//시작버튼
	auto timer = Timer::create(10.0f);
	puzzle_me.virus = Object::create("images/bubble3.png", puzzlebackground, puzzle_me.x, puzzle_me.y, false);

	//start2 이벤트(즉, 퍼즐 시작)
	timer->setOnTimerCallback([&](TimerPtr) -> bool
		{
			hearts[life].heart->hide();
			life++;

			if (life == 3) {
				endGame();
			}
			else {
				puzzle_me.virus->hide();
				for (int i = 0; i < many; i++) {
					balls[random[i]].virus->setImage("images/bubble5.png");
					kids[random[i]].virus->hide();
				}
				start->show();
				conti->enter();
				party->hide();
				showMessage("생명이 하나 줄었어!ㅜㅜ 그래도 아직 기회는 남아있지!!\n 또 도전할 거면 go! 포기할 거면 stop!");
			}
			return true;
		});
	again->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		puzzlebackground->enter();
		cout << "how many viruses do you want to kill?(less than 35): ";
		cin >> many;
		if (many > 35) {
			cout << "less than 35!";
			cout << "how many?(less than 35): ";
			cin >> many;
		}
		random = new int[many];
		for (int i = 0; i < many; i++) {
			random[i] = many + 1;
		}
		return true;
		});
	end->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});
	start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		timer->set(10.f);
		showTimer(timer);
		timer->start();
		start->hide();

		for (int i = 0; i < many; i++) {
			random[i] = many + 1;
		}

		int i = 0;
		for (i = 0; i < many; i++) {
			bool ok = true;
			int randint = rand() % 35;
			for (int r = 0; r < i; r++) { // 같은 인덱스의 세균인 경우에 다시 생성하기
				if (random[r] == randint) {
					ok = false;
				}
			}
			if (ok) {
				random[i] = randint;
			}
			else {
				i--;
				continue;
			}
			kids[random[i]].virus->show();

			puzzle_me.x = kids[i].x + 128;
			puzzle_me.y = kids[i].y;
			puzzle_me.virus->locate(puzzlebackground, puzzle_me.x, puzzle_me.y);
			puzzle_me.virus->show();
		}
		return true;
		});


	puzzle_me.virus->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (action == MouseAction::MOUSE_DRAG_LEFT) {
			bool unique = true;
			if (puzzle_me.x != left) {
				int narin = 0;
				puzzle_me.x = puzzle_me.x - 128;
				puzzle_me.virus->locate(puzzlebackground, puzzle_me.x, puzzle_me.y);
				for (int i = 0; i < many; i++) {
					if ((puzzle_me.x == kids[random[i]].x) && (puzzle_me.y == kids[random[i]].y)) {
						for (int r = 0; r < many; r++) {
							narin = 0;
							if (path[r][0] == puzzle_me.x && path[r][1] == puzzle_me.y) {
								unique = false;//이미 같은 패스를 지난 경우->움직이지 않도록
							}
						}
						if (unique) {
							balls[random[i]].virus->setImage("images/bubble6.png");
							kids[random[i]].virus->hide();
							p++;
							path[p][0] = puzzle_me.x;
							path[p][1] = puzzle_me.y;
						}
					}
				}
			}
		}
		if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			bool unique = true;
			if (puzzle_me.x != left + 768) {
				puzzle_me.x = puzzle_me.x + 128;
				puzzle_me.virus->locate(puzzlebackground, puzzle_me.x, puzzle_me.y);
				for (int i = 0; i < many; i++) {
					if ((puzzle_me.x == kids[random[i]].x) && (puzzle_me.y == kids[random[i]].y)) {
						for (int r = 0; r < many; r++) {
							if (path[r][0] == puzzle_me.x && path[r][1] == puzzle_me.y) {
								unique = false;//이미 같은 패스를 지난 경우->움직이지 않도록
							}
						}
						if (unique) {
							balls[random[i]].virus->setImage("images/bubble6.png");
							kids[random[i]].virus->hide();
							p++;
							path[p][0] = puzzle_me.x;
							path[p][1] = puzzle_me.y;
						}
					}
				}
			}
		}
		if (action == MouseAction::MOUSE_DRAG_UP) {
			bool unique = true;
			if (puzzle_me.y != 600) {
				puzzle_me.y = puzzle_me.y + 128;
				puzzle_me.virus->locate(puzzlebackground, puzzle_me.x, puzzle_me.y);//이동시킨 애: j
				for (int i = 0; i < many; i++) {
					if ((puzzle_me.x == kids[random[i]].x) && (puzzle_me.y == kids[random[i]].y)) {
						for (int r = 0; r < many; r++) {
							if (path[r][0] == puzzle_me.x && path[r][1] == puzzle_me.y) {
								unique = false;//이미 같은 패스를 지난 경우->움직이지 않도록
							}
						}
						if (unique) {
							balls[random[i]].virus->setImage("images/bubble6.png");
							kids[random[i]].virus->hide();
							p++;
							path[p][0] = puzzle_me.x;
							path[p][1] = puzzle_me.y;
						}
					}
				}
			}
		}
		if (action == MouseAction::MOUSE_DRAG_DOWN) {
			bool unique = true;
			if (puzzle_me.y != height) {
				int narin = 0;
				puzzle_me.y = puzzle_me.y - 128;
				puzzle_me.virus->locate(puzzlebackground, puzzle_me.x, puzzle_me.y);//이동시킨 애: j
				for (int i = 0; i < many; i++) {
					if ((puzzle_me.x == kids[random[i]].x) && (puzzle_me.y == kids[random[i]].y)) {
						for (int r = 0; r < many; r++) {
							narin = 0;
							if (path[r][0] == puzzle_me.x && path[r][1] == puzzle_me.y) {
								unique = false;// 같은 패스를 지난 경우->움직이지 않도록
							}
						}
						if (unique) {
							balls[random[i]].virus->setImage("images/bubble6.png");//배경노란색 공
							kids[random[i]].virus->hide();//세균
							p++;
							path[p][0] = puzzle_me.x;
							path[p][1] = puzzle_me.y;

						}
					}
				}
			}
		}
		if (p == many) {//세균을 다 없앴다면
			p = 0;
			timer->stop();
			puzzle_me.virus->hide();
			for (int i = 0; i < many; i++) {
				balls[random[i]].virus->setImage("images/bubble5.png");
			}
			start->show();
			conti->enter();
			party->show();
			showMessage("축하축하!\n 새로운 청소 게임을 하고 싶으면 go!, 끝내고 싶으면 stop을 눌러줘!");

		}
		return true;

		});

	startGame(puzzlebackground);

}