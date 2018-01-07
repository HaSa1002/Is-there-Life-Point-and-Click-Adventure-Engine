#include "Rendering.hpp"

#include <imgui-SFML.h>

namespace pc {
	void Rendering::render() {
		window.clear();
		for each (std::shared_ptr<sf::Drawable> drawable in draw_list) {
			window.draw(*drawable);
		}
		if (draw_imgui)
			ImGui::SFML::Render(window);
		window.display();
	}

	void Rendering::createWindow() {
		window.create(sf::VideoMode(1600, 900), "ITLengine", sf::Style::Default);
		title = "ITLengine";
	}

	void Rendering::createWindow(sf::VideoMode video_mode) {
		window.create(video_mode, "ITLengine", sf::Style::Default);
		title = "ITLengine";
	}

	void Rendering::createWindow(const std::string& title, const bool fullscreen, sf::VideoMode video_mode) {
			if (fullscreen)
				window.create(video_mode, title, sf::Style::Fullscreen);
			else
				window.create(video_mode, title, sf::Style::Default);
			this->title = title;
	}

	Rendering::Rendering() {

	}

	Rendering::~Rendering() {
		if (isOpen())
			window.close();
	}

	void Rendering::imgui_rendering(bool draw)
	{
		draw_imgui = draw;
	}

	void Rendering::closeWindow() {
		window.close();
	}

	auto Rendering::getVideoModes()-> const std::vector<sf::VideoMode> {
		return sf::VideoMode::getFullscreenModes();
	}

	auto Rendering::getWindowObject() -> sf::RenderWindow&
	{
		return this->window;
	}

	bool Rendering::isOpen()
	{
		return window.isOpen();
	}

	void Rendering::move(const sf::Vector2f& offset) {
		view.move(offset);
		this->offset += offset;
	}

	void Rendering::zoom(const float factor, bool anitmated) {
		view.zoom(factor);
	}

	void Rendering::reset() {
		view.move(-this->offset);
		this->offset = sf::Vector2f(0, 0);
		view.setRotation(0);
		view.zoom(1);
	}

	void Rendering::remove(std::shared_ptr<sf::Drawable> element) {

	}
}