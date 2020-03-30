#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glm/glm.hpp>

#include <cstdint>
#include <vector>
#include <utility>

namespace aur
{
    class Texture
    {
    public:
        enum Mode
        {
            Addition,
            Subtraction,
            ReverseSubtraction,
            Modulation,
            Decaling
        };

        enum WrapMode
        {
            Repeat,
            MirroredRepeat,
            ClampToEdge
        };

        enum FilterType
        {
            Nearest,
            Linear,
            NearestMipmapNearest,
            NearestMipmapLinear,
            LinearMipmapNearest,
            LinearMipmapLinear
        };

        Texture(std::vector<uint8_t> image_data, unsigned int width, unsigned int height, unsigned int channels)
            : _image_data{std::move(image_data)}, _width{width}, _height{height}, _channels{channels}
        {}

        virtual ~Texture() = default;

        [[nodiscard]] const std::vector<uint8_t> &get_image_data() const
        {
            return _image_data;
        }

        void set_image_data(const std::vector<uint8_t> &image_data)
        {
            _image_data = image_data;
            _requires_data_update = true;
        }

        [[nodiscard]] unsigned int get_width() const
        {
            return _width;
        }

        void set_width(unsigned int width)
        {
            if (_width != width) {
                _width = width;
                _requires_data_update = true;
            }
        }

        [[nodiscard]] unsigned int get_height() const
        {
            return _height;
        }

        void set_height(unsigned int height)
        {
            if (_height != height) {
                _height = height;
                _requires_data_update = true;
            }
        }

        [[nodiscard]] unsigned int get_channels() const
        {
            return _channels;
        }

        void set_channels(unsigned int channels)
        {
            if (_channels != channels) {
                _channels = channels;
                _requires_data_update = true;
            }
        }

        [[nodiscard]] bool is_enabled() const
        {
            return _enabled;
        }

        void set_enabled(bool enabled)
        {
            _enabled = enabled;
        }

        [[nodiscard]] bool requires_params_update() const
        {
            return _requires_params_update;
        }

        void set_requires_params_update(bool requires_params_update)
        {
            _requires_params_update = requires_params_update;
        }

        [[nodiscard]] bool requires_data_update() const
        {
            return _requires_data_update;
        }

        void set_requires_data_update(bool requires_data_update)
        {
            _requires_data_update = requires_data_update;
        }

        [[nodiscard]] bool are_mipmaps_enabled() const
        {
            return _mipmaps_enabled;
        }

        void set_mipmaps_enabled(bool mipmaps_enabled)
        {
            if (_mipmaps_enabled != mipmaps_enabled) {
                _mipmaps_enabled = mipmaps_enabled;
                _requires_data_update = true;
            }
        }

        [[nodiscard]] Mode get_mode() const
        {
            return _mode;
        }

        void set_mode(Mode mode)
        {
            _mode = mode;
        }

        [[nodiscard]] WrapMode get_wrap_mode_s() const
        {
            return _wrap_mode_s;
        }

        void set_wrap_mode_s(WrapMode wrap_mode_s)
        {
            if (_wrap_mode_s != wrap_mode_s) {
                _wrap_mode_s = wrap_mode_s;
                _requires_params_update = true;
            }
        }

        [[nodiscard]] WrapMode get_wrap_mode_t() const
        {
            return _wrap_mode_t;
        }

        void set_wrap_mode_t(WrapMode wrap_mode_t)
        {
            if (_wrap_mode_t != wrap_mode_t) {
                _wrap_mode_t = wrap_mode_t;
                _requires_params_update = true;
            }
        }

        [[nodiscard]] FilterType get_minification_filter() const
        {
            return _minification_filter;
        }

        void set_minification_filter(FilterType minification_filter)
        {
            if (_minification_filter != minification_filter) {
                _minification_filter = minification_filter;
                _requires_params_update = true;
            }
        }

        [[nodiscard]] FilterType get_magnification_filter() const
        {
            return _magnification_filter;
        }

        void set_magnification_filter(FilterType magnification_filter)
        {
            if (_magnification_filter != magnification_filter) {
                _magnification_filter = magnification_filter;
                _requires_params_update = true;
            }
        }

        [[nodiscard]] float get_anisotropy() const
        {
            return _anisotropy;
        }

        void set_anisotropy(float anisotropy)
        {
            if (_anisotropy != anisotropy) {
                _anisotropy = anisotropy;
                _requires_params_update = true;
            }
        }

        [[nodiscard]] bool is_transformation_enabled() const
        {
            return _transformation_enabled;
        }

        void set_transformation_enabled(bool transformation_enabled)
        {
            _transformation_enabled = transformation_enabled;
        }

        [[nodiscard]] const glm::mat4 &get_transformation_matrix() const
        {
            return _transformation_matrix;
        }

        void set_transformation_matrix(const glm::mat4 &transformation_matrix)
        {
            _transformation_matrix = transformation_matrix;
        }

        virtual void update(unsigned int sampler) = 0;

        virtual void use(unsigned int sampler) = 0;

    protected:
        bool _enabled{true};
        bool _requires_params_update{true};
        bool _requires_data_update{true};
        std::vector<uint8_t> _image_data;

        unsigned int _width;
        unsigned int _height;
        unsigned int _channels;

        bool _mipmaps_enabled{false};
        Mode _mode{Mode::Modulation};
        WrapMode _wrap_mode_s{ClampToEdge};
        WrapMode _wrap_mode_t{ClampToEdge};
        FilterType _minification_filter{Linear};
        FilterType _magnification_filter{Linear};
        float _anisotropy{0.0f};

        bool _transformation_enabled{false};
        glm::mat4 _transformation_matrix{1.0f};
    };
}

#endif
