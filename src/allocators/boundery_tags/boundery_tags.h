#ifndef BOUNDERY_TAGS_H
#define BOUNDERY_TAGS_H

#include "../../memory/memory.h"
#include "../../logger/logger_holder.h"
#include "../../logger/logger.h"
#include "../../logger/logger_concrete.h"
#include "../../memory/memory_holder.h"
#include <cstring>
//TODO поменять на норм название, ПОТОМ КОГДА-НИБУДЬ
class boundery_tags final : public memory, protected logger_holder
{
private:
	void* _all_memory;

protected:
	size_t get_service_part_allocator_size() const;
	void** get_first_occup_block() const;
	size_t get_allocator_size() const;
	size_t get_occup_block_serv_size() const;
	void** get_pointer_prev_block(void* target_ptr) const;
	void** get_pointer_next_block(void* target_ptr) const;
	size_t get_size_block(void* target_ptr) const;
	void dump_allocator_state(bool is_allocate) const noexcept;
	logger* get_logger() const noexcept override;
	void debug_alloc(const void* target_ptr) const;
	std::pair<void*, size_t> get_aviable_block_address_and_size(
		void* const previous_occupied_block_address,
		void* const next_occupied_block_address) const;
	std::string get_address(void* target_ptr) const override;
	std::string get_allocate_mode_string(allocate_mode method) const;

protected:
	void dump_allocate(void* target_ptr,
		size_t target_size,
		logger* log) const override {};


public:
	void* allocate(size_t target_size) const override;

public:
	void deallocate(void const* const target_to_dealloc) const override;

public:
	boundery_tags(logger* log, memory* allocator, size_t size, memory::allocate_mode method);

public:
	boundery_tags(boundery_tags const&) = delete;
	boundery_tags& operator=(boundery_tags const&) = delete;

public:
	~boundery_tags();
};

#endif // BOUNDERY_TAGS_H