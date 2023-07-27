#include "shell.h"
/**
* mem_copy - implementation of a memory copy function.
* @destination: A void pointer to the destination
* where the data will be copied.
* @source: A const void pointer to the source data that needs to be copied.
* @size: An unsigned integer representing the number of bytes to be copied
* from the source to the destination.
*/

void mem_copy(void *destination, const void *source, unsigned int size)
{
	char *dest_ptr = (char *)destination;
	const char *src_ptr = (const char *)source;
	unsigned int index;

	for (index = 0; index < size; index++)
		dest_ptr[index] = src_ptr[index];
}

/**
* _realloc - implementation of realloc.
* @old_ptr: previously allocated memory.
* @old_size: space allocated to ptr.
* @new_size: new allocated space.
*
* Return: pointer to head node.
*/

void *_realloc(void *old_ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (old_ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (old_ptr);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (new_size < old_size)
		mem_copy(new_ptr, old_ptr, new_size);
	else
		mem_copy(new_ptr, old_ptr, old_size);
	free(old_ptr);
	return (new_ptr);
}

/**
* _reallocdptr - reallocate memmory to double pointer.
* @old_ptr: A void pointer to the destination where the data will be copied.
* @old_size: allocated space.
* @new_size: new allocated space.
*
* Return: double pointer to head node.
*/

char **_reallocdptr(char **old_ptr, unsigned int old_size,
		unsigned int new_size)
{
	unsigned int i;
	char **new_ptr;

	if (new_size == old_size)
		return (old_ptr);
	if (old_ptr == NULL)
		return (malloc(sizeof(char *) * new_size));
	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);
	for  (i = 0; i < old_size; i++)
		new_ptr[i] = old_ptr[i];
	free(old_ptr);
	return (new_ptr);
}
