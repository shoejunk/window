export module stk.window;

import std.core;
import stk.ds;
import stk.input;
import stk.log;
import <SFML/Graphics.hpp>;
import <cassert>;

using namespace std;
using namespace stk;

namespace stk
{
	export class c_window
	{
	public:
		c_window(uint32_t x, uint32_t y, char const* Title)
			: m_window(sf::VideoMode(x, y), Title)
		{
		}

		bool is_open() const { return m_window.isOpen(); }

		bool update()
		{
			m_input.reset();
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
					return false;
				}
				else
				{
					m_input.on(event);
				}
			}

			m_window.clear(sf::Color::Black);
			for (const auto& drawable : m_drawables)
			{
				assert(drawable != nullptr);
				m_window.draw(*drawable);
			}
			m_window.display();
			return true;
		}

		void make_sprite(std::string const& image_path, float x, float y)
		{
			try
			{
				m_textures.emplace();
				sf::Texture& tex = m_textures[m_textures.count() - 1];
				if (tex.loadFromFile(image_path))
				{
					try
					{
						auto sprite = std::make_shared<sf::Sprite>(tex);
						sprite->setPosition(x, y);
						sprite->setScale(0.2f, 0.2f);
						if (!m_drawables.append(sprite))
						{
							errorln("Failed to append sprite to drawables");
							m_textures.remove_at_unordered(m_textures.count() - 1);
							return;
						}
					}
					catch (...)
					{
						errorln("Failed to create sprite from texture: ", image_path);
						m_textures.remove_at_unordered(m_textures.count() - 1);
						return;
					}
				}
				else
				{
					errorln("Failed to load image from file: ", image_path);
					m_textures.remove_at_unordered(m_textures.count() - 1);
					return;
				}
			}
			catch (...)
			{
				errorln("Failed to load texture: ", image_path);
				return;
			}
		}

		bool add_drawable(std::shared_ptr<sf::Drawable> drawable)
		{
			return m_drawables.append(drawable);
		}

	private:
		sf::RenderWindow m_window;
		ds::fixed_vector<sf::Texture, 512> m_textures;
		ds::fixed_vector<std::shared_ptr<sf::Drawable>, 1024> m_drawables;
		c_input m_input;
	};
}
