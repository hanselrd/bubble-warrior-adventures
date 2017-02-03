#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>

namespace bwa {
	namespace detail {
		/*
			Checks if an object has a loadFromFile function
			Almost all SFML resources have this function
		*/
		template <typename T, typename Enable = void>
		struct has_loadFromFile_function
			: std::false_type {};

		template <typename T>
		struct has_loadFromFile_function<T,
			std::void_t<decltype(std::declval<T>().loadFromFile(""))>>
			: std::true_type {};

		/*
			Checks if an object has a openFromFile function
			For example sf::Music
		*/
		template <typename T, typename Enable = void>
		struct has_openFromFile_function
			: std::false_type {};

		template <typename T>
		struct has_openFromFile_function<T,
			std::void_t<decltype(std::declval<T>().openFromFile(""))>>
			: std::true_type {};

		/*
			The implementation of the Resource object
			Resources are stored in maps by their unique type
			so loading an sf::Texture and an sf::Font would yield
			two maps. This is so that if you try to retrieve a resource
			with the wrong time you get a runtime error for
			accessing a key that doesn't exist.
		*/
		template <typename T, typename Enable = void>
		struct Resource_impl {};

		/*
			Overload for SFML objects that export a
			loadFromFile function
		*/
		template <typename T>
		struct Resource_impl<T,
			std::enable_if_t<detail::has_loadFromFile_function<T>::value>> {
			static std::shared_ptr<T> load(const std::string& filename) {
				auto ptr = std::make_shared<T>();
				ptr->loadFromFile(filename);
				return std::move(ptr);
			}
		};

		/*
			Overload for SFML objects that export a
			openFromFile function
		*/
		template <typename T>
		struct Resource_impl<T,
			std::enable_if_t<detail::has_openFromFile_function<T>::value>> {
			static std::shared_ptr<T> load(const std::string& filename) {
				auto ptr = std::make_shared<T>();
				ptr->openFromFile(filename);
				return std::move(ptr);
			}
		};
	}

	/*
		The interface to load or get a resource
	*/
	template <typename T>
	struct Resource final : public detail::Resource_impl<T> {
		static std::shared_ptr<T> get(const std::string& filename) {
			if (_map.count(filename))
				return _map.at(filename);
			else
				return load(filename);
		}
	private:
		static std::map<std::string, std::shared_ptr<T>> _map;
	};

	template <typename T>
	std::map<std::string, std::shared_ptr<T>> Resource<T>::_map;
}
