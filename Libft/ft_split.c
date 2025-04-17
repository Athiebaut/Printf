/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:13:45 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/10 15:13:51 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * This function is used to free memory allocated for an array of strings
 * and its individual elements. It iterates through the array, freeing each
 * string, and then frees the array itself.
 *
 * @param ptr A pointer to the array of strings to be freed.
 * @param i The number of elements in the array that need to be freed.
 *          This is typically the number of strings already allocated
 *          before an error occurred.
 *
 * @return Always returns NULL (0) to indicate the array has been freed.
 */
static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}


/**
 * @brief Splits a string into an array of words based on a delimiter.
 *
 * This function allocates memory for and populates an array of strings (`s2`)
 * by splitting the input string `s` into words separated by the character `c`.
 * The number of words to split is specified by `num_words`.
 *
 * @param s The input string to be split.
 * @param c The delimiter character used to separate words.
 * @param s2 A pre-allocated array of strings to store the resulting words.
 * @param num_words The number of words to extract from the input string.
 * 
 * @return A pointer to the array of strings (`s2`) containing the split words,
 *         or NULL if memory allocation fails.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       array of strings (`s2`) and its contents.
 *
 * @warning If memory allocation for any word fails, the function will free
 *          any previously allocated memory and return NULL.
 */
static char	**ft_split_words(char const *s, char c, char **s2, int num_words)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < num_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		s2[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!s2)
			return (free_array(s2, word));
		ft_putword(s2[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	s2[word] = 0;
	return (s2);
}

/**
 * ft_split - Splits a string into an array of strings based on a delimiter.
 * 
 * @s: The input string to be split. Must be a null-terminated string.
 * @c: The delimiter character used to split the string.
 * 
 * Return: A pointer to an array of strings (char **), where each string is a 
 *         segment of the input string separated by the delimiter. The array 
 *         is null-terminated. Returns NULL if memory allocation fails or if 
 *         the input string is NULL.
 * 
 * Note: The function relies on helper functions `ft_count_words` to count the 
 *       number of words in the input string and `ft_split_words` to perform 
 *       the actual splitting and allocation of the strings.
 */
char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num_words;

	if (!s)
		return (0);
	num_words = ft_count_words(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!s2)
		return (0);
	s2 = ft_split_words(s, c, s2, num_words);
	return (s2);
}
