/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:20:38 by bsavinel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/14 14:31:20 by bsavinel         ###   ########.fr       */
=======
/*   Updated: 2022/05/14 14:51:07 by omoudni          ###   ########.fr       */
>>>>>>> 54e4a5afe4b1e1b3fb152566c74be0159cc7fb52
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

#define GREEN "\033[92;m"
#define YEL "\033[93;m"
#define WHITE "\033[0;m"
#define RESET "\033[0;m"

int string_all_lower(std::string line)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (!islower(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int ft_is_in_dico(std::set<std::string> possible_words, std::string word)
{
	if (possible_words.find(word) != possible_words.end())
		return (1);
	return (0);
}

<<<<<<< HEAD
void	ft_print_display(std::vector<std::string> tab)
{
	std::cout << " *************" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << " * " << tab[i] << std::endl << " * ";
	}
	std::cout << " *************" << std::endl;
}

void	ft_game_loop(std::set<std::string> possible_words, std::vector<std::string> win_words)
{
	int							nb_tours;
	std::vector<std::string>	tab;
	std::string					word;
	std::string					hidden;
=======
int	ft_nbr_occurences(char c, std::string widden)
{
	int nbr;
	int i;

	nbr = 0;
	i = 0;
	while (widden[i])
	{
		if (widden[i] == c)
			nbr++;
		i++;
	}
	return (nbr);
}

int ft_letter_in_widden(std::string word, std::string widden, int i, int *found_already)
{
	int j;

	j = 0;
	while (widden[j])
	{
		if (widden[j] == word[i] && *found_already <= ft_nbr_occurences(word[i], ft_letter_in_widden))
		{
			*found_already++;
			return (1);
		}
		j++;
	}
	return (0);
}

std::string ft_color_letters(std::string word, std::string widden)
{
	int i;
	int found_already;
	std::string res;

	found_already = 0;
	i = 0;
	while (i < 5)
	{
		if (word[i] == widden[i])
			res = res + GREEN + word[i] + RESET;
		else if (ft_letter_in_widden(word, widden, i, &found_already))
			res = res + YEL + word[i] + RESET;
		i++;
	}
	return (res);
}

void ft_game_loop(std::set<std::string> possible_words, std::set<std::string> win_words)
{
	int nb_tours;
	std::vector<std::string> tab;
	std::string word;
>>>>>>> 54e4a5afe4b1e1b3fb152566c74be0159cc7fb52

	nb_tours = 0;
	for (int i = 0; i < 6; i++)
	{
		tab.push_back("- - - - -");
	}
	nb_tours = 0;
	hidden = win_words[rand() % (win_words.size() - 1)];
	possible_words.insert(hidden);
	while (nb_tours < 6)
	{
		ft_print_display(tab);
		std::cout << "\nEnter a word (5 letters, lowercase): ";
		getline(std::cin, word);
		if (word.size() != 5 || !ft_is_in_dico(possible_words, word))
		{
			std::cout << "Invalid word" << std::endl;
			continue;
		}
		tab[nb_tours] = ft_color_letters(word, hidden);
		if (hidden == word)
		{
			ft_print_display(tab);
			std::cout << "\nCONGRATULATION : YOU WIN !!!!!!!" << std::endl;
			return ;
		}l
		nb_tours++;
	}
<<<<<<< HEAD
	std::cout << "\nSory : you lose\n The word has :" << hidden << std::endl;
=======
>>>>>>> 54e4a5afe4b1e1b3fb152566c74be0159cc7fb52
}

int main(int ac, char **av)
{
<<<<<<< HEAD
	std::ifstream				ifs;
	std::string					line;
	std::vector<std::string>	win_words;
	std::set<std::string>		possible_words;
	int							i;
=======
	std::ifstream ifs;
	std::string line;
	std::set<std::string> win_words;
	std::set<std::string> possible_words;
	int i;
>>>>>>> 54e4a5afe4b1e1b3fb152566c74be0159cc7fb52

	/* ************************************************************************** */
	/*					Put and check the dictionary in all words				  */
	/* ************************************************************************** */

	if (ac != 3)
	{
		std::cout << "Please lunch the Wordle with two dictionary" << std::endl;
		return (1);
	}

	ifs.open(av[1]);
	if (!ifs)
	{
		std::cout << "Bad dico" << std::endl;
		return (1);
	}
	while (getline(ifs, line))
	{
		if (line.size() == 5 && string_all_lower(line))
		{
			std::cout << "Word : '" << line << "' is not vallid word" << std::endl;
			return (1);
		}
		possible_words.insert(line);
	}
	ifs.close();
	if (possible_words.size() == 0)
	{
		std::cout << "No word in the dictionary" << std::endl;
		return (1);
	}

	ifs.open(av[2]);
	if (!ifs)
	{
		std::cout << "Bad dico" << std::endl;
		return (1);
	}
	while (getline(ifs, line))
	{
		if (line.size() == 5 && string_all_lower(line))
		{
			std::cout << "Word : '" << line << "' is not vallid word" << std::endl;
			return (1);
		}
		win_words.push_back(line);
	}
	ifs.close();
	if (win_words.size() == 0)
	{
		std::cout << "No word in the dictionary" << std::endl;
		return (1);
	}
	return (ft_game_loop(possible_words, win_words), 0);
}
