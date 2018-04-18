#include "ordered_array.h"
#include "kheap.h"

signed char standard_lessthan_predicate(type_t a, type_t b)
{
	return (a<b)?1:0;
}

ordered_array_t create_ordered_array(unsigned int max_size, lessthan_predicate_t less_than)
{
	ordered_array_t to_ret;
	to_ret.array = (void*)kmalloc(max_size*sizeof(type_t));
	memset((unsigned char *)to_ret.array, 0, max_size*sizeof(type_t));
	to_ret.size = 0;
	to_ret.max_size = max_size;
	to_ret.less_than = less_than;
	return to_ret;
}

ordered_array_t place_ordered_array(void *addr, unsigned int max_size, lessthan_predicate_t less_than)
{
	ordered_array_t to_ret;
	to_ret.array = (type_t*)addr;
	memset((unsigned char *)to_ret.array, 0, max_size*sizeof(type_t));
	to_ret.size = 0;
	to_ret.max_size = max_size;
	to_ret.less_than = less_than;
	return to_ret;
}

void destroy_ordered_array(ordered_array_t *array)
{
	kfree(array->array);
}

void insert_ordered_array(type_t item, ordered_array_t *array)
{
	ASSERT(array->less_than);
	ASSERT(array->size + 1 < array->max_size);

	unsigned int iterator = 0;
	while (iterator < array->size && array->less_than(array->array[iterator], item)) {
		iterator++;
	}

	if (iterator == array->size) {
		array->array[array->size++] = item;
	} else {
		type_t tmp = array->array[iterator];
		array->array[iterator] = item;
		while (iterator < array->size) {
			iterator++;
			type_t tmp2 = array->array[iterator];
			array->array[iterator] = tmp;
			tmp = tmp2;
		}
		array->size++;
	}

}

type_t lookup_ordered_array(unsigned int i, ordered_array_t *array)
{
	ASSERT(i < array->size);
	return array->array[i];
}

void remove_ordered_array(unsigned int i, ordered_array_t *array)
{
	while (i < array->size)
	{
		i++;
		array->array[i] = array->array[i];
	}
	array->size--;
}