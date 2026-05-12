#include "Player.h"

#include <graphics.h>
#include <easyx.h>
#include <Windows.h>
#pragma comment(lib, "Msimg32.lib")
#include "Projection.h"

// 玩家贴图
IMAGE playerImg;

bool playerImgLoaded = false;

void Player::Update()
{
    if (gameOver)
    {
        // ESC退出游戏

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }

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

        if (enemies[i].z < 240)
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

        box.x = (rand() % 5 - 2) * 100;

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

                // 生成命中特效
                HitEffect fx;

                fx.x = enemies[j].x;
                fx.z = enemies[j].z;

                hitEffects.push_back(fx);

                if (enemies[j].hp <= 0)
                {
                    enemies[j].alive = false;
                    killCount++;
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

                    boxes[j].hp--;
                    
                    // 蓝色命中特效

                    HitEffect fx;

                    fx.x = boxes[j].x;
                    fx.z = boxes[j].z;

                    fx.color = RGB(80, 180, 255);

                    hitEffects.push_back(fx);

                    if (boxes[j].hp <= 0)
                    {
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
    // 更新特效

    for (int i = 0; i < hitEffects.size(); i++)
    {
        hitEffects[i].Update();
    }

    // 删除特效

    for (int i = 0; i < hitEffects.size();)
    {
        if (!hitEffects[i].alive)
        {
            hitEffects.erase(
                hitEffects.begin() + i
            );
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

   

    // 基地防线

   // =========================
// 能量防线
// =========================

    int left = 180;
    int right = 720;
    int top = 710;
    int bottom = 748;

    // 外层辉光

    setfillcolor(RGB(40, 120, 255));

    solidrectangle(
        left - 6,
        top - 6,
        right + 6,
        bottom + 6
    );

    // 主体

    setfillcolor(RGB(80, 200, 255));

    solidrectangle(
        left,
        top,
        right,
        bottom
    );

    // 内层高光

    setfillcolor(RGB(180, 255, 255));

    solidrectangle(
        left,
        top + 6,
        right,
        top + 12
    );

    // 能量线

    setlinecolor(RGB(255, 255, 255));

    for (int i = left; i < right; i += 40)
    {
        line(
            i,
            top,
            i + 20,
            bottom
        );
    }

    // HP文字

    settextcolor(WHITE);

    TCHAR hpText[64];

    swprintf_s(
        hpText,
        L"BASE HP : %d",
        baseHP
    );

    outtextxy(
        330,
        680,
        hpText
    );
    // 玩家

// 玩家PNG透明绘制

    BLENDFUNCTION blend =
    {
        AC_SRC_OVER,
        0,
        255,
        AC_SRC_ALPHA
    };

    int playerSize = 180;

    AlphaBlend(
        GetImageHDC(NULL),
        screenX - playerSize / 2,
        screenY - playerSize / 2,
        playerSize,
        playerSize,

        GetImageHDC(&playerImg),
        0,
        0,
        128,
        128,

        blend
    );
    // 命中特效

    for (int i = 0; i < hitEffects.size(); i++)
    {
        hitEffects[i].Draw();
    }
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

    // =========================
// GAME OVER UI
// =========================

    if (gameOver)
    {
        // 半透明黑幕

        setfillcolor(RGB(0, 0, 0));

        solidrectangle(
            120,
            180,
            780,
            620
        );

        // 红色标题

        settextcolor(RGB(255, 80, 80));

        settextstyle(
            72,
            0,
            L"Consolas"
        );

        outtextxy(
            190,
            230,
            L"GAME OVER"
        );

        // 击杀统计

        TCHAR text[128];

        swprintf_s(
            text,
            128,
            L"Milk Frog Kills : %d",
            killCount
        );

        settextcolor(WHITE);

        settextstyle(
            36,
            0,
            L"微软雅黑"
        );

        outtextxy(
            280,
            360,
            text
        );

        // Wave

        TCHAR waveText[64];

        swprintf_s(
            waveText,
            64,
            L"Final Wave : %d",
            wave
        );

        outtextxy(
            250,
            430,
            waveText
        );

        // 提示

        settextcolor(RGB(180, 180, 180));

        settextstyle(
            24,
            0,
            L"Consolas"
        );

        outtextxy(
            250,
            540,
            L"Press ESC To Exit"
        );
    }
}