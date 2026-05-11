#include "Player.h"

#include <graphics.h>
#include <easyx.h>
#include <Windows.h>

#include "Projection.h"

// 玩家贴图
IMAGE playerImg;

bool playerImgLoaded = false;

void Player::Update()
{
    if (gameOver)
    {
        return;
    }

    // 左右移动

    if (GetAsyncKeyState('A'))
    {
        x -= 8;
    }

    if (GetAsyncKeyState('D'))
    {
        x += 8;
    }

    // 边界

    if (x < -300)
    {
        x = -300;
    }

    if (x > 300)
    {
        x = 300;
    }

    // 自动开火

    shootTimer++;

    if (shootTimer >= shootDelay)
    {
        shootTimer = 0;

        Bullet bullet;

        bullet.x = x;

        bullet.z = 220;

        bullets.push_back(bullet);

        if (powerLevel >= 2)
        {
            Bullet b1;
            b1.x = x - 25;
            b1.z = 180;
            bullets.push_back(b1);

            Bullet b2;
            b2.x = x + 25;
            b2.z = 180;
            bullets.push_back(b2);
        }

        if (powerLevel >= 3)
        {
            Bullet b3;
            b3.x = x - 50;
            b3.z = 140;
            bullets.push_back(b3);

            Bullet b4;
            b4.x = x + 50;
            b4.z = 140;
            bullets.push_back(b4);
        }
    }

    // 更新子弹

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update();
    }

    // 删除子弹

    for (int i = 0; i < bullets.size();)
    {
        if (!bullets[i].alive)
        {
            bullets.erase(bullets.begin() + i);
        }
        else
        {
            i++;
        }
    }

    // Wave

    waveTimer++;

    if (waveTimer >= 600)
    {
        waveTimer = 0;

        wave++;
    }

    // 敌人生成

    enemyTimer++;

    int spawnDelay = 180 - wave * 5;

    if (spawnDelay < 40)
    {
        spawnDelay = 40;
    }

    if (enemyTimer >= spawnDelay)
    {
        enemyTimer = 0;

        int enemyCount = 3 + wave / 2;

        int start = -(enemyCount / 2);
        int end = enemyCount / 2;

        for (int i = start; i <= end; i++)
        {
            Enemy enemy;

            enemy.x = i * 150;

            enemy.z = 1000;

            enemy.speed = 6 + wave * 0.6f;

            enemy.hp = 1 + wave / 3;

            enemies.push_back(enemy);
        }
    }

    // 更新敌人

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update();

        if (enemies[i].z < 140)
        {
            enemies[i].alive = false;

            baseHP--;

            if (baseHP <= 0)
            {
                gameOver = true;
            }
        
        }
    }

    // 宝箱生成

    boxTimer++;

    if (boxTimer >= 420)
    {
        boxTimer = 0;

        Box box;

        box.x = 300;

        box.z = 1000;

        boxes.push_back(box);
    }

    // 更新宝箱

    for (int i = 0; i < boxes.size(); i++)
    {
        boxes[i].Update();
    }

    // 子弹碰撞敌人

    for (int i = 0; i < bullets.size(); i++)
    {
        ProjectionResult bp =
            Projection::Project(
                bullets[i].x,
                bullets[i].z
            );

        int bulletSize =
            (int)(12 * bp.scale);

        if (bulletSize < 2)
        {
            bulletSize = 2;
        }

        for (int j = 0; j < enemies.size(); j++)
        {
            ProjectionResult ep =
                Projection::Project(
                    enemies[j].x,
                    enemies[j].z
                );

            int enemySize =
                (int)(40 * ep.scale);

            if (enemySize < 10)
            {
                enemySize = 10;
            }

            int dx =
                bp.screenX - ep.screenX;

            int dy =
                bp.screenY - ep.screenY;

            int rr =
                bulletSize + enemySize;

            if (dx * dx + dy * dy < rr * rr)
            {
                bullets[i].alive = false;

                enemies[j].hp--;

                if (enemies[j].hp <= 0)
                {
                    enemies[j].alive = false;
                }

                break;
            }
        }
    }
    
        // 子弹碰撞宝箱

        for (int i = 0; i < bullets.size(); i++)
        {
            ProjectionResult bp =
                Projection::Project(
                    bullets[i].x,
                    bullets[i].z
                );

            for (int j = 0; j < boxes.size(); j++)
            {
                ProjectionResult xp =
                    Projection::Project(
                        boxes[j].x,
                        boxes[j].z
                    );

                int dx =
                    bp.screenX - xp.screenX;

                int dy =
                    bp.screenY - xp.screenY;

                if (dx * dx + dy * dy < 2500)
                {
                    bullets[i].alive = false;

                    boxes[j].alive = false;

                    // 强化等级

                    powerLevel++;

                    if (powerLevel > 3)
                    {
                        powerLevel = 3;
                    }

                    // 提高射速

                    if (shootDelay > 6)
                    {
                        shootDelay--;
                    }
                }
            }
        }

    // 删除宝箱

    for (int i = 0; i < boxes.size();)
    {
        if (!boxes[i].alive)
        {
            boxes.erase(boxes.begin() + i);
        }
        else
        {
            i++;
        }
    }
    

    // 删除敌人

    for (int i = 0; i < enemies.size();)
    {
        if (!enemies[i].alive)
        {
            enemies.erase(enemies.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void Player::Draw()
{
    const int screenW = 900;
    const int screenH = 900;

    int screenX =
        screenW / 2 + (int)x;

    int screenY = 810;

    // 加载玩家PNG

    if (!playerImgLoaded)
    {
        loadimage(
            &playerImg,
            L"Player.png",
            128,
            128,
            true
        );

        playerImgLoaded = true;
    }

    // 敌人

  // 先画左右敌人
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].x != 0)
        {
            enemies[i].Draw();
        }
    }

    // 最后画中间敌人
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].x == 0)
        {
            enemies[i].Draw();
        }
    }

    // 宝箱

    for (int i = 0; i < boxes.size(); i++)
    {
        boxes[i].Draw();
    }

    // 玩家

    putimage(
        screenX - 64,
        screenY - 64,
        &playerImg
    );

    // 基地防线

    setfillcolor(RGB(80, 180, 255));

    solidrectangle(
        180,
        720,
        720,
        750
    );

    // 子弹（最后画）

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }

    // UI

    settextcolor(WHITE);

    TCHAR text[64];

    swprintf_s(
        text,
        L"Power:%d  HP:%d  Wave:%d",
        powerLevel,
        baseHP,
        wave
    );

    outtextxy(
        20,
        20,
        text
    );

    // GAME OVER

    if (gameOver)
    {
        settextcolor(RED);

        settextstyle(
            60,
            0,
            L"Consolas"
        );

        outtextxy(
            250,
            300,
            L"GAME OVER"
        );
    }
}