import stk.window;

using namespace stk;

int main()
{
	c_window window(1280, 720, "My Window");
	const float cell_size = 80.0f;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			auto cell = std::make_shared<sf::RectangleShape>(sf::Vector2f(cell_size, cell_size));
			cell->setPosition(x * cell_size, y * cell_size);
			cell->setFillColor((x + y) % 2 == 0 ? sf::Color(240, 217, 181) : sf::Color(181, 136, 99));
			window.add_drawable(cell);
		}
	}

	window.make_sprite("data/rocket.png", 800.f, 0.f);
	window.make_sprite("data/alien.png", 800.f, 350.f);

	while (window.update())
	{
	}
	return 0;
}
