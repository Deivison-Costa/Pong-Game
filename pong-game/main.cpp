#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");
    window.setFramerateLimit(60);

    // Paddle settings
    const float paddleWidth = 20.0f;
    const float paddleHeight = 100.0f;
    sf::RectangleShape leftPaddle(sf::Vector2f(paddleWidth, paddleHeight));
    sf::RectangleShape rightPaddle(sf::Vector2f(paddleWidth, paddleHeight));

    leftPaddle.setFillColor(sf::Color::White);
    rightPaddle.setFillColor(sf::Color::White);

    const float paddleSpeed = 5.0f;

    // Ball settings
    const float ballRadius = 10.0f;
    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::White);

    float ballSpeedX = 5.0f;
    float ballSpeedY = 5.0f;

    // Initial positions
    leftPaddle.setPosition(50, window.getSize().y / 2 - paddleHeight / 2);
    rightPaddle.setPosition(window.getSize().x - 50 - paddleWidth, window.getSize().y / 2 - paddleHeight / 2);
    ball.setPosition(window.getSize().x / 2 - ballRadius, window.getSize().y / 2 - ballRadius);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle paddle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            leftPaddle.move(0, -paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            leftPaddle.move(0, paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rightPaddle.move(0, -paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            rightPaddle.move(0, paddleSpeed);
        }

        // Ball movement
        ball.move(ballSpeedX, ballSpeedY);

        // Ball collisions with window borders
        if (ball.getPosition().y <= 0 || ball.getPosition().y >= window.getSize().y - 2 * ballRadius) {
            ballSpeedY = -ballSpeedY;
        }

        // Ball collisions with paddles
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballSpeedX = -ballSpeedX;
        }

        // Ball out of bounds
        if (ball.getPosition().x <= 0 || ball.getPosition().x >= window.getSize().x - 2 * ballRadius) {
            ball.setPosition(window.getSize().x / 2 - ballRadius, window.getSize().y / 2 - ballRadius);
            ballSpeedX = -ballSpeedX;
        }

        window.clear();
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}
