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
		video_mode = sf::VideoMode(1600, 900);
		window.create(video_mode, title, sf::Style::Resize | sf::Style::Close);
	}

	void Rendering::createWindow(sf::VideoMode video_mode) {
		this->video_mode = video_mode;
		window.create(video_mode, title, sf::Style::Resize);
	}

	void Rendering::createWindow(const std::string& title, const bool fullscreen, sf::VideoMode video_mode) {
		this->fullscreen = fullscreen;
		if (fullscreen)
			window.create(video_mode, title, sf::Style::Fullscreen);
		else
			window.create(video_mode, title, sf::Style::Default);
		this->title = title;
		this->video_mode = video_mode;
	}

	Rendering::Rendering(mb::Bus& message_bus) : bus{ message_bus } {
		//std::function<void(mb::Message)> render_reciever = [this](mb::Message message) {};
		std::function<void(mb::Message)> render_reciever = [this](mb::Message message) {
			this->reciever(message);
		};
		bus.subscribe(mb::MessageType::sfEvent, render_reciever);
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

	void Rendering::reciever(mb::Message message) {
		const sf::Event* event = static_cast<const sf::Event*>(message.data.at(0));
		switch (event->type) {
		case sf::Event::Closed:
			closeWindow();
			break;
		case sf::Event::Resized:
			closeWindow();
			video_mode = sf::VideoMode(event->size.width, event->size.height);
			createWindow(title, fullscreen, video_mode);
			break;
		case sf::Event::LostFocus:
			break;
		case sf::Event::GainedFocus:
			break;
		case sf::Event::TextEntered:
			break;
		case sf::Event::KeyPressed:
			break;
		case sf::Event::KeyReleased:
			break;
		case sf::Event::MouseWheelMoved:
			break;
		case sf::Event::MouseWheelScrolled:
			break;
		case sf::Event::MouseButtonPressed:
			break;
		case sf::Event::MouseButtonReleased:
			break;
		case sf::Event::MouseMoved:
			break;
		case sf::Event::MouseEntered:
			break;
		case sf::Event::MouseLeft:
			break;
		case sf::Event::JoystickButtonPressed:
			break;
		case sf::Event::JoystickButtonReleased:
			break;
		case sf::Event::JoystickMoved:
			break;
		case sf::Event::JoystickConnected:
			break;
		case sf::Event::JoystickDisconnected:
			break;
		case sf::Event::TouchBegan:
			break;
		case sf::Event::TouchMoved:
			break;
		case sf::Event::TouchEnded:
			break;
		case sf::Event::SensorChanged:
			break;
		default:
			break;
		}
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