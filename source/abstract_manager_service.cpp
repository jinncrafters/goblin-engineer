#include <goblin-engineer/abstract_manager_service.hpp>
#include <goblin-engineer/dynamic_environment.hpp>
#include <iostream>

namespace goblin_engineer {

    using abstract_environment = actor_zeta::environment::abstract_environment;

    template <class Sender >
    inline auto send(const Sender& actor,message msg){
        actor->enqueue(std::move(msg));
    }

    abstract_manager_service::abstract_manager_service(dynamic_environment *env, actor_zeta::detail::string_view name)
        : lite(name)
        , executor_(env->executor())
        {
    }

    auto abstract_manager_service::join(base_actor *t) -> actor_zeta::actor_address {
        auto address = t->address();
        storage_.emplace_back(t);
        return address;
    }

    auto abstract_manager_service::broadcast(message msg) -> bool {
        auto msg_tmp = std::move(msg);
        for (auto &i:storage_) {
            send(i, msg_tmp.clone());
        }
        return true;
    }

    auto abstract_manager_service::executor() noexcept -> actor_zeta::executor::abstract_executor & {
        return executor_;
    }

    void abstract_manager_service::enqueue(message msg, actor_zeta::executor::execution_device *) {
        actor_zeta::context tmp(this,std::move(msg));
        dispatch().execute(tmp);
    }
}

