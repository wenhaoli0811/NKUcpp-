#include "Player.h"

#include <graphics.h>
#include <Windows.h>
#include <vector>

void Player::Update()
{
    // 左右移动
    if (GetAsyncKeyState('A'))
    {
        x -= 8;
    }

    if (GetAsyncKeyState('D'))
    {
        x += 8;
    }

    // 边界限制
    if (x < -300) x = -300;
    if (x > 300) x = 300;

    // 自动开火
    shootTimer++;
    if (shootTimer >= 10)
    {
        shootTimer = 0;
        Bullet bullet;
        bullet.x = x;
        bullet.z = 0;
        bullets.push_back(bullet);
    }

    // 更新所有子弹
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update();
    }

    // 删除失效子弹
    for (int i = 0; i < bullets.size();)
    {
        if (!bullets[i].alive)
            bullets.erase(bullets.begin() + i);
        else
            i++;
    }

    // 敌人生成计时
    enemyTimer++;
    if (enemyTimer >= 60) // 每60帧生成一波
    {
        enemyTimer = 0;
        // 生成整齐队列
        for (int i = -2; i <= 2; i++)
        {
            Enemy enemy;
            enemy.x = i * 120;
            enemy.z = 1000;
            enemies.push_back(enemy);
        }
    }

    // 更新敌人
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update();
    }

    // 子弹碰撞敌人
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int j = 0; j < enemies.size(); j++)
        {
            float dx = bullets[i].x - enemies[j].x;
            float dz = bullets[i].z - enemies[j].z;
            if (dx * dx + dz * dz < 2500) // 碰撞判断
            {
                bullets[i].alive = false;
                enemies[j].hp--;
                if (enemies[j].hp <= 0)
                    enemies[j].alive = false;
            }
        }
    }

    // 删除死亡敌人
    for (int i = 0; i < enemies.size();)
    {
        if (!enemies[i].alive)
            enemies.erase(enemies.begin() + i);
        else
            i++;
    }
}

void Player::Draw()
{
    const int screenW = 900;
    const int screenH = 900;

    // 玩家位置
    int screenX = screenW / 2 + (int)x;
    int screenY = screenH - 180;

    // 车身
    setfillcolor(RGB(120, 120, 120));
    solidrectangle(screenX - 50, screenY - 40, screenX + 50, screenY + 40);

    // 炮管
    setfillcolor(YELLOW);
    solidrectangle(screenX - 8, screenY - 70, screenX + 8, screenY - 20);

    // 左轮
    setfillcolor(BLUE);
    solidcircle(screenX - 35, screenY + 45, 12);

    // 右轮
    solidcircle(screenX + 35, screenY + 45, 12);

    // 绘制子弹
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }

    // 绘制敌人
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}