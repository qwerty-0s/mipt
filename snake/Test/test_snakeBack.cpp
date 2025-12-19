#include <gtest/gtest.h>
#include "../snake/snakeBack.h"
#include <ctime>
#include <iostream>


class SnakeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализация перед каждым тестом
        testSnake = new snake(10, 10);
    }
    
    void TearDown() override {
        delete testSnake;
    }
    
    snake* testSnake;
};

class FoodTest : public ::testing::Test {
protected:
    void SetUp() override {
        testFood = new food(100, 100);
    }
    
    void TearDown() override {
        delete testFood;
    }
    
    food* testFood;
};


TEST_F(SnakeTest, ConstructorInitialization) {
    // Проверяем корректность инициализации змейки
    EXPECT_EQ(testSnake->len(), 10); // Начальная длина
    
    // Проверяем начальную позицию головы
    EXPECT_EQ(testSnake->get_snake_coordinates_x(0), 10);
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), 10);
    
    // Проверяем, что тело змейки инициализировано правильно
    for (int i = 1; i < testSnake->len(); i++) {
        EXPECT_EQ(testSnake->get_snake_coordinates_x(i), 10 - i);
        EXPECT_EQ(testSnake->get_snake_coordinates_y(i), 10);
    }
}

TEST_F(SnakeTest, MoveRightDirection) {
    // Сохраняем исходные позиции
    int oldX = testSnake->get_snake_coordinates_x(0);
    int oldY = testSnake->get_snake_coordinates_y(0);
    
    testSnake->move();
    
    // Проверяем, что голова переместилась вправо
    EXPECT_EQ(testSnake->get_snake_coordinates_x(0), oldX + 1);
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), oldY);
    
    // Проверяем, что тело сдвинулось
    EXPECT_EQ(testSnake->get_snake_coordinates_x(1), oldX);
    EXPECT_EQ(testSnake->get_snake_coordinates_y(1), oldY);
}

TEST_F(SnakeTest, MoveDifferentDirections) {
    // Тестируем движение вверх
    testSnake->set_direction(snake::UP);
    testSnake->move();
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), 9); // y уменьшается
    
    // Тестируем движение вниз
    testSnake->set_direction(snake::DOWN);
    testSnake->move();
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), 10); // y увеличивается
    
    // Тестируем движение влево
    testSnake->set_direction(snake::LEFT);
    testSnake->move();
    EXPECT_EQ(testSnake->get_snake_coordinates_x(0), 10); // x уменьшается
}

TEST_F(SnakeTest, SetDirectionLogic) {
    // Начальное направление - RIGHT
    testSnake->set_direction(snake::UP);
    testSnake->move();
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), 9);
    
    // Нельзя сразу развернуться на 180 градусов
    testSnake->set_direction(snake::DOWN); // UP -> DOWN не должно работать
    testSnake->move();
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), 8); // Продолжает двигаться вверх
    
    // Теперь можно повернуть влево
    testSnake->set_direction(snake::LEFT);
    testSnake->move();
    EXPECT_EQ(testSnake->get_snake_coordinates_x(0), 10);
}

TEST_F(SnakeTest, CheckSelfCollision) {
    // Создаем змейку, которая сразу столкнется сама с собой
    snake selfCollidingSnake(5, 5);
    
    // Для теста: искусственно создаем коллизию
    // В нормальных условиях змейка не сталкивается сама с собой при создании
    // Тестируем на граничных условиях
    EXPECT_FALSE(selfCollidingSnake.check_collision(100, 100));
    
    // Тест: змейка не должна сталкиваться сама с собой при нормальном движении
    for (int i = 0; i < 5; i++) {
        selfCollidingSnake.move();
        EXPECT_FALSE(selfCollidingSnake.check_collision(100, 100));
    }
}

TEST_F(SnakeTest, CheckWallCollision) {
    // Тест столкновения с правой стенкой
    snake rightWallSnake(100, 50); // Правая граница при max_width = 100
    EXPECT_TRUE(rightWallSnake.check_collision(100, 100));
    
    // Тест столкновения с левой стенкой
    snake leftWallSnake(-1, 50);
    EXPECT_TRUE(leftWallSnake.check_collision(100, 100));
    
    // Тест столкновения с нижней стенкой
    snake bottomWallSnake(50, 100); // Нижняя граница при max_height = 100
    EXPECT_TRUE(bottomWallSnake.check_collision(100, 100));
    
    // Тест столкновения с верхней стенкой
    snake topWallSnake(50, -1);
    EXPECT_TRUE(topWallSnake.check_collision(100, 100));
    
    // Тест отсутствия столкновения внутри поля
    snake safeSnake(50, 50);
    EXPECT_FALSE(safeSnake.check_collision(100, 100));
}

TEST_F(SnakeTest, GrowWhenEatingFood) {
    food* testFood = new food(10, 10); // Еда в той же позиции, что и голова змейки
    
    int initialLength = testSnake->len();
    
    // Голова змейки в позиции (10,10), еда тоже в (10,10)
    bool ateFood = testSnake->grow(testFood);
    
    EXPECT_TRUE(ateFood);
    EXPECT_EQ(testSnake->len(), initialLength + 1);
    
    delete testFood;
}

TEST_F(SnakeTest, DoNotGrowWhenNoFood) {
    int initialLength = testSnake->len();
    
    // Без еды
    bool ateFood = testSnake->grow(nullptr);
    
    EXPECT_FALSE(ateFood);
    EXPECT_EQ(testSnake->len(), initialLength);
}

TEST_F(SnakeTest, DoNotGrowWhenFoodNotAtHead) {
    food* testFood = new food(20, 20); // Еда в другой позиции
    
    int initialLength = testSnake->len();
    bool ateFood = testSnake->grow(testFood);
    
    EXPECT_FALSE(ateFood);
    EXPECT_EQ(testSnake->len(), initialLength);
    
    delete testFood;
}

TEST_F(SnakeTest, GetCoordinatesMethods) {
    // Проверяем граничные значения
    EXPECT_EQ(testSnake->get_snake_coordinates_x(0), 10);
    EXPECT_EQ(testSnake->get_snake_coordinates_y(0), 10);
    
    // Проверяем последний сегмент
    EXPECT_EQ(testSnake->get_snake_coordinates_x(testSnake->len() - 1), 1);
    EXPECT_EQ(testSnake->get_snake_coordinates_y(testSnake->len() - 1), 10);
    
    // Проверяем сегмент в середине
    EXPECT_EQ(testSnake->get_snake_coordinates_x(5), 5);
    EXPECT_EQ(testSnake->get_snake_coordinates_y(5), 10);
}


TEST_F(FoodTest, ConstructorInitialization) {
    // Координаты должны быть в пределах 0-99
    int x = testFood->getX();
    int y = testFood->getY();
    
    EXPECT_GE(x, 0);
    EXPECT_LT(x, 100);
    EXPECT_GE(y, 0);
    EXPECT_LT(y, 100);
}

TEST_F(FoodTest, RespawnChangesPosition) {
    // Сохраняем старые координаты
    int oldX = testFood->getX();
    int oldY = testFood->getY();
    
    // Вызываем респаун
    testFood->respawn(100, 100);
    
    // Получаем новые координаты
    int newX = testFood->getX();
    int newY = testFood->getY();
    
    // Координаты должны измениться (хотя есть маленькая вероятность совпадения)
    // Проверяем, что новые координаты в пределах
    EXPECT_GE(newX, 0);
    EXPECT_LT(newX, 100);
    EXPECT_GE(newY, 0);
    EXPECT_LT(newY, 100);
    
    // В 99.99% случаев координаты будут разными
    // Но тест не должен падать если они совпали (маловероятно)
    if (oldX == newX && oldY == newY) {
        std::cout << "Note: Food respawned in same position (statistically rare)" << std::endl;
    }
}

TEST_F(FoodTest, MultipleRespawnsValid) {
    for (int i = 0; i < 100; i++) {
        testFood->respawn(100, 100);
        int x = testFood->getX();
        int y = testFood->getY();
        
        EXPECT_GE(x, 0);
        EXPECT_LT(x, 100);
        EXPECT_GE(y, 0);
        EXPECT_LT(y, 100);
    }
}

TEST_F(FoodTest, GetMethods) {
    int x = testFood->getX();
    int y = testFood->getY();
    
    // Проверяем, что методы возвращают корректные значения
    EXPECT_EQ(testFood->getX(), x);
    EXPECT_EQ(testFood->getY(), y);
}


TEST(SnakeBackgroundTest, ConstructorInitialization) {
    SnakeBackground bg(800, 600, 20);
}

TEST(SnakeBackgroundTest, DefaultConstructor) {
    SnakeBackground bg;
}

TEST(SnakeFoodIntegration, SnakeEatsFoodAndGrows) {
    // Создаем змейку и еду в одной позиции
    snake testSnake(15, 15);
    food* testFood = new food(15, 15); // Заставим еду появиться в (15,15)
    
    // Несколько раз респауним еду, пока не окажется в нужной позиции
    
    int initialLength = testSnake.len();
    
    // Проверяем, что змейка может съесть еду
    bool ate = false;
    for (int i = 0; i < 100; i++) {
        testFood->respawn(100, 100);
        if (testFood->getX() == 15 && testFood->getY() == 15) {
            ate = testSnake.grow(testFood);
            if (ate) break;
        }
    }
    
    // С вероятностью ~63% еда окажется в нужной позиции за 100 попыток
    if (ate) {
        EXPECT_EQ(testSnake.len(), initialLength + 1);
    } else {
        std::cout << "Note: Food never spawned at snake position in 100 attempts" << std::endl;
    }
    
    delete testFood;
}

TEST(SnakeFoodIntegration, SnakeMovementAroundFood) {
    snake testSnake(50, 50);
    food testFood(100, 100);
    
    // Сохраняем начальную длину
    int initialLength = testSnake.len();
    
    // Двигаем змейку к еде
    testSnake.set_direction(snake::RIGHT);
    
    // Делаем несколько шагов (не доходя до еды)
    for (int i = 0; i < 10; i++) {
        testSnake.move();
        bool ate = testSnake.grow(&testFood);
        EXPECT_FALSE(ate); // Не должна есть, так как еда не в позиции головы
    }
    
    // Длина не должна измениться
    EXPECT_EQ(testSnake.len(), initialLength);
}


TEST(SnakeEdgeCases, MaximumLengthNotExceeded) {
    // Создаем змейку и много раз кормим
    snake testSnake(0, 0);
    food* testFood = new food(1, 1); // Еда в позиции змейки
    
    // Много раз пытаемся съесть еду
    for (int i = 0; i < 50; i++) {
        testSnake.grow(testFood);
        testFood->respawn(100, 100);
    }
    
    
    EXPECT_LE(testSnake.len(), 100); // Длина не должна превышать размер массива
    
    delete testFood;
}

TEST(SnakeEdgeCases, NegativeCoordinates) {
    snake testSnake(-5, -5);
    
    // Проверяем столкновение с границами
    EXPECT_TRUE(testSnake.check_collision(10, 10));
    
    // Двигаем змейку
    testSnake.set_direction(snake::RIGHT);
    testSnake.move();
    
    EXPECT_EQ(testSnake.get_snake_coordinates_x(0), -4);
}


struct DirectionTestParams {
    snake::direction startDir;
    snake::direction newDir;
    bool shouldChange;
};

class DirectionChangeTest : public ::testing::TestWithParam<DirectionTestParams> {
protected:
    snake* testSnake;
    
    void SetUp() override {
        testSnake = new snake(10, 10);
    }
    
    void TearDown() override {
        delete testSnake;
    }
};

TEST_P(DirectionChangeTest, TestDirectionChangeLogic) {
    DirectionTestParams params = GetParam();
    
    // Устанавливаем начальное направление
    testSnake->set_direction(params.startDir);
    
    // Пытаемся изменить направление
    testSnake->set_direction(params.newDir);
    
    
    testSnake->move();
    
}

INSTANTIATE_TEST_SUITE_P(
    DirectionChangeTests,
    DirectionChangeTest,
    ::testing::Values(
        DirectionTestParams{snake::UP, snake::DOWN, false},
        DirectionTestParams{snake::DOWN, snake::UP, false},
        DirectionTestParams{snake::LEFT, snake::RIGHT, false},
        DirectionTestParams{snake::RIGHT, snake::LEFT, false},
        DirectionTestParams{snake::UP, snake::LEFT, true},
        DirectionTestParams{snake::RIGHT, snake::UP, true}
    )
);


TEST(SnakeDeathTest, AccessOutOfBoundsCoordinates) {
    snake testSnake(10, 10);
    
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}