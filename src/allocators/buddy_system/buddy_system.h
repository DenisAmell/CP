#ifndef BUDDY_SYSTEM_H
#define BUDDY_SYSTEM_H

#include "../../memory/memory.h"
#include "../../logger/logger.h"
#include "../../logger/logger_concrete.h"
#include "../../logger/logger_holder.h"

class buddy_system final : public memory, private logger_holder
{

private:
	void* _all_memory;

protected:
	size_t get_block_avail_size(void* target_ptr) const;
	size_t get_occup_block_serv_size() const;
	size_t get_avail_block_serv_size() const;
	void* get_pointer_avail_prev_block(void* target_ptr) const;
	void* get_pointer_avail_next_block(void* target_ptr) const;
	void* get_first_avail_block() const;
	void** get_first_avail_block_ptr() const;
	size_t get_service_part_allocator_size() const;
	void dump_allocator_state(bool is_allocate) const noexcept;
	std::string get_pointer_address(void* target_ptr) const;
	void debug_alloc(const void* target_ptr) const;
	std::string get_allocate_mode_string(allocate_mode method) const;
	logger* get_logger() const noexcept override;
	unsigned char compact_block_size_and_block_occup(size_t size_as_power_of_2, bool block_occup) const;
	void* get_buddies(void* target_ptr) const;
	bool is_free_block(void* target_ptr) const;
	memory* get_memory() const;

public:
	virtual void* allocate(size_t requested_block_size) const override;

public:
	virtual void deallocate(void const* const block_to_deallocate_address) const override;

protected:
	virtual void dump_allocate(void* target_ptr,
		size_t target_size,
		logger* log) const override {};
protected:
	virtual std::string get_address(void* target_ptr) const override { return "gg"; };

public:
	buddy_system(logger* log,
		memory* allocator,
		size_t size,
		allocate_mode method);
	~buddy_system();
};

#endif //BUDDY_SYSTEM_H