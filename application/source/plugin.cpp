#include <iostream>
#include "../header/application/plugin.hpp"
#include "../header/application/abstract_plugin.hpp"
#include "../header/application/metadata.hpp"
namespace application {

    inline std::string name(abstract_plugin* ptr){
        std::string tmp;
        tmp = ptr->metadata()->name;
        return tmp;
    }

    void plugin::state(state_t state_) {
        this->state_ = state_;
    }

    state_t plugin::state() const {
        return state_;
    }

    plugin::plugin(abstract_plugin *ptr) :
            plugin_(ptr), state_(state_t::registered){}

    result plugin::call(const std::string &method, virtual_args &&args) {
        std::cerr << "execute:" << name(self()) << std::endl;
        if (state() == state_t::started) {
            return self()->call(method,std::forward<virtual_args>(args));
        } else {
            std::cerr << "error execute plugin: " << name(self()) << std::endl;
            return result();
        }
    }

    void plugin::startup(const boost::program_options::variables_map &options) {
        std::cerr << "startup plugin: " << name(self()) << std::endl;
        if (state() == state_t::initialized) {
            state(state_t::started);
            return self()->startup(options);
        } else {
            std::cerr << "error startup  plugin: " << name(self()) << std::endl;
        }
    }

    void plugin::initialization(context_t *context) {
        std::cerr << "initialization plugin: " << name(self()) << std::endl;
        if (state() == state_t::registered) {
            state(state_t::initialized);
            return self()->initialization(context);
        } else {
            std::cerr << "error initialization plugin: " << name(self()) << std::endl;
        }
    }

    void plugin::shutdown() {
        std::cerr << "shutdown plugin:" << name(self()) << std::endl;
        if (state() == state_t::started) {
            state(state_t::stopped);
            return self()->shutdown();
        } else {
            std::cerr << "error shutdown plugin:" << name(self()) << std::endl;
        }

    }

    metadata_t *plugin::metadata() const {
        return self()->metadata();
    }
}