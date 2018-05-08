#include "Rendering.hpp"

//#include <imgui-SFML.h>

namespace pc {

	Rendering::~Rendering() {
		//close the window if open
		if (isOpen())
			window.close();
	}

	void Rendering::add(std::shared_ptr<sf::Drawable> object, int layer) {
		if (layer >= draw_list.size())
			draw_list.resize(layer + 1);
		draw_list[layer].push_back(object);
	}

	void Rendering::addEditor(std::shared_ptr<sf::Drawable> object, int layer) {
		if (layer >= editor_list.size())
			editor_list.resize(layer + 1);
		editor_list[layer].push_back(object);
	}


	////////////////////////////////////////////////////////////
	void Rendering::createWindow(sf::VideoMode video_mode) {
		createWindow("Is there Life? | Engine", false, video_mode);
	}


	////////////////////////////////////////////////////////////
	void Rendering::createWindow(const std::string& title, const bool& fullscreen, const sf::VideoMode& vid_mode) {
		this->fullscreen = fullscreen;
		if (vid_mode.height == 0 && vid_mode.width == 0) {
			if (fullscreen)
				this->video_mode = video_mode.getFullscreenModes()[0];
			else
				this->video_mode = video_mode.getDesktopMode();
		} else
			this->video_mode = vid_mode;
			
		if (fullscreen)
			window.create(video_mode, title, sf::Style::Fullscreen);
		else
			window.create(video_mode, title, sf::Style::Default);
		this->title = title;

		window.resetGLStates();
		window.setVerticalSyncEnabled(true);
		ImGui::SFML::Init(window);
	}

	auto Rendering::getTime() -> const sf::Time {
		return clock.getElapsedTime();
	}


	void Rendering::addGUI(std::shared_ptr<sf::Drawable> gui_element, int layer) {
		if (layer >= gui_list.size())
			gui_list.resize(layer + 1);
		gui_list[layer].push_back(gui_element);
	}

	////////////////////////////////////////////////////////////
	void Rendering::closeWindow() {
		ImGui::SFML::Shutdown();
		window.close();
	}


	////////////////////////////////////////////////////////////
	auto Rendering::getVideoModes()-> const std::vector<sf::VideoMode> {
		return video_mode.getFullscreenModes();
	}


	////////////////////////////////////////////////////////////
	auto Rendering::getWindowObject() -> sf::RenderWindow& {
		return window;
	}


	////////////////////////////////////////////////////////////
	void Rendering::imgui_rendering(bool draw) {
		draw_imgui = draw;
	}


	////////////////////////////////////////////////////////////
	bool Rendering::isOpen() {
		return window.isOpen();
	}


	////////////////////////////////////////////////////////////
	void Rendering::move(const sf::Vector2f& offset) {
		view.move(offset);
		this->offset += offset;
	}

	void Rendering::newImGuiWindow() {
		ImGui::SFML::Update(window, clock.restart());
	}


	////////////////////////////////////////////////////////////
	void Rendering::processEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (draw_imgui)
				ImGui::SFML::ProcessEvent(event);
			
			switch (event.type) {
			case sf::Event::Closed:
				closeWindow();
				break;
			case sf::Event::Resized:
				closeWindow();
				video_mode = sf::VideoMode(event.size.width, event.size.height);
				createWindow(title, fullscreen, video_mode);
				break;
			case sf::Event::LostFocus:
				has_focus = false;
				break;
			case sf::Event::GainedFocus:
				has_focus = true;
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
			events.push(sf::Event(event));
		}
	}


	////////////////////////////////////////////////////////////
	void Rendering::remove(std::shared_ptr<sf::Drawable> element) {

	}

	void Rendering::remove() {
		draw_list.clear();
	}

	void Rendering::removeEditor() {
		editor_list.clear();
	}

	void Rendering::removeGUI(std::shared_ptr<sf::Drawable> gui_element) {
		for (auto& draw_layer : gui_list)
			draw_layer.remove(gui_element);
	}


	////////////////////////////////////////////////////////////
	void Rendering::render() {
		if (has_focus) {
			window.clear();
			for (auto& draw_layer : draw_list) {
				for (auto& drawable : draw_layer) {
					window.draw(*drawable);
					//Space for optimisations
				}
			}
			for (auto& draw_layer : editor_list) {
				for (auto& drawable : draw_layer) {
					window.draw(*drawable);
					//Space for optimisations
				}
			}
			for (auto& draw_layer : gui_list) {
				for (auto& drawable : draw_layer) {
					window.draw(*drawable);
					//Space for optimisations
				}
			}
			if (draw_imgui)
				ImGui::SFML::Render(window);
		}
		window.display();
		processEvents();
		
	}


	void Rendering::removeGUI() {
		gui_list.clear();
	}

	////////////////////////////////////////////////////////////
	void Rendering::reset() {
		view.move(-this->offset);
		this->offset = sf::Vector2f(0, 0);
		view.setRotation(0);
		view.zoom(1);
	}


	////////////////////////////////////////////////////////////
	void Rendering::zoom(const float factor, bool anitmated) {
		view.zoom(factor);

		//TODO: Animation
	}


}