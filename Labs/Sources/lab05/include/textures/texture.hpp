#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstdint>
#include <vector>
#include <utility>

namespace aur {
    class Texture {
    public:
        Texture(std::vector<uint8_t> image_data, unsigned int width, unsigned int height, unsigned int channels)
            : _image_data { std::move(image_data) }, _width { width }, _height { height }, _channels { channels } { }

        virtual ~Texture() = default;

        const std::vector<uint8_t> &get_image_data() const {
            return _image_data;
        }

        void set_image_data(const std::vector<uint8_t> &image_data) {
            _image_data = image_data;
            set_requires_update(true);
        }

        unsigned int get_width() const {
            return _width;
        }

        void set_width(unsigned int width) {
            if (_width != width) {
                _width = width;
                set_requires_update(true);
            }
        }

        unsigned int get_height() const {
            return _height;
        }

        void set_height(unsigned int height) {
            if (_height != height) {
                _height = height;
                set_requires_update(true);
            }
        }

        unsigned int get_channels() const {
            return _channels;
        }

        void set_channels(unsigned int channels) {
            if (_channels != channels) {
                _channels = channels;
                set_requires_update(true);
            }
        }

        int get_texture() const {
            return _texture;
        }

        bool is_requires_update() const {
            return _requires_update;
        }

        void set_requires_update(bool requires_update) {
            _requires_update = requires_update;
        }

        virtual void update() = 0;

        virtual void use() = 0;

    protected:
        bool _requires_update { true };
        std::vector<uint8_t> _image_data;

        unsigned int _width;
        unsigned int _height;
        unsigned int _channels;

        int _texture { -1 };
    };
}

#endif
