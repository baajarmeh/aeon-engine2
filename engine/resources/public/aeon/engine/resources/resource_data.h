// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/engine/resources/export.h>
#include <aeon/common/uuid.h>
#include <set>

namespace aeon::engine::resources
{

class AEON_ENGINE_RESOURCES_EXPORT resource_data
{
public:
    using resource_id = common::uuid;

    virtual ~resource_data();

    resource_data(const resource_data &) = delete;
    auto operator=(const resource_data &) -> resource_data & = delete;

    resource_data(resource_data &&) noexcept = default;
    auto operator=(resource_data &&) noexcept -> resource_data & = default;

    /*!
     * Returns the unique id of this resource
     */
    [[nodiscard]] auto id() const noexcept -> const resource_id &;

    /*!
     * Get the allocator this resource was created with.
     */
    [[nodiscard]] auto get_allocator() const noexcept -> std::pmr::memory_resource *;

    /*!
     * Returns the resources that this resource depends on (for example a mesh depends on a material)
     */
    [[nodiscard]] virtual auto dependencies() const noexcept -> std::pmr::set<resource_id> = 0;

protected:
    explicit resource_data(std::pmr::memory_resource *allocator = std::pmr::get_default_resource()) noexcept;
    explicit resource_data(const resource_id &id, std::pmr::memory_resource *allocator = std::pmr::get_default_resource());

private:
    std::pmr::memory_resource *allocator_;
    resource_id id_;
};

} // namespace aeon::engine::resources
