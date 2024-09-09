import stk.window;

using namespace stk;

int main()
{
	c_window window(1280, 720, "My Window");
	window.make_sprite("data/rocket.png", 0.f, 0.f);
	window.make_sprite("data/alien.png", 500.f, 0.f);
	while (window.update())
	{
	}
	return 0;
}
