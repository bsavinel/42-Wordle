/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:20:38 by bsavinel          #+#    #+#             */
/*   Updated: 2022/05/14 17:28:02 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <time.h>
#include <cctype>


#define GREEN "\33[0;32m"
#define GREENB "\33[1;32m"
#define YEL "\33[93m"
#define YELB "\33[1;93m"
#define REDB "\33[31;1m"
#define WHITE "\33[0m"
#define RESET "\33[0m"

typedef struct s_nbletter
{
 	int	nb_occurence;
 	int nb_green;
	int	nb_yellow;
} t_nbletter;

int string_all_lower(std::string line)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (!islower(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_display(std::vector<std::string> tab)
{
	std::cout << " *************" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << " * " << tab[i].c_str()  << " * " << std::endl;
	}
	std::cout << " *************" << std::endl;
}

int ft_is_in_dico(std::set<std::string> possible_words, std::string word)
{
	if (possible_words.find(word) != possible_words.end())
		return (1);
	return (0);
}





int	ft_nbr_occurences(char c, std::string hidden)
{
	int nbr;
	int i;

	nbr = 0;
	i = 0;
	while (hidden[i])
	{
		if (hidden[i] == c)
			nbr++;
		i++;
	}
	return (nbr);
}

void	feed_info(t_nbletter info[256], std::string word, std::string hidden)
{
	int	i = 0;

	while (i < 5)
	{
		info[(int)word[i]].nb_occurence = ft_nbr_occurences(word[i], hidden);
		if (word[i] == hidden[i])
			info[(int)word[i]].nb_green++;
		i++;
	}
	for (int j = 0; j < 256; j++)
	{
		info[j].nb_yellow = info[j].nb_occurence - info[j].nb_green;
	}
}

int	is_in_str(char c, std::string hidden)
{
	int i;

	i = 0;
	while (hidden[i])
	{
		if (hidden[i] == c)
			return (1);
		i++;
	}
	return (0);
}

std::string	create_str(t_nbletter info[256], std::string word, std::string hidden)
{
	std::string res;
	int i = 0;

	while (i < 5)
	{
		if (word[i] == hidden[i])
			res = res + GREENB + (char)toupper(word[i]) + RESET;
		else if (is_in_str(word[i], hidden) && info[(int)word[i]].nb_yellow > 0)
		{
			res = res + YELB + (char)toupper(word[i]) + RESET;
			info[(int)word[i]].nb_yellow--;
		}
		else
			res = res + (char)toupper(word[i]);
		if (i < 4)
			res = res + " ";
		i++;
	}
	return (res);
}

std::string ft_color_letters(std::string word, std::string hidden)
{
	t_nbletter info[256];
	
	for (int j = 0; j < 256; j++)
	{
		info[j].nb_occurence = 0;
		info[j].nb_green = 0;
		info[j].nb_yellow = 0;
	}
	feed_info(info, word, hidden);
	return (create_str(info, word, hidden));
}












void ft_game_loop(std::set<std::string> possible_words, std::vector<std::string> win_words)
{
	int							nb_tours;
	std::vector<std::string>	tab;
	std::string					word;
	std::string					hidden;

	nb_tours = 0;
	for (int i = 0; i < 6; i++)
	{
		tab.push_back("- - - - -");
	}
	srand (time(NULL));
	nb_tours = 0;
	hidden = win_words[rand() % (win_words.size() - 1)];
	possible_words.insert(hidden);
	while (nb_tours < 5)
	{
		ft_print_display(tab);
		std::cout << "\nEnter a word (5 letters): ";
		if (!getline(std::cin, word))
		{
			std::cout << "\nVery bad problem encountered" << std::endl;
			return ;
		}
		for (int i = 0; i < (int)word.size(); i++)
		{
			word[i] = (char)tolower(word[i]);
		}
		if (word.size() != 5 || !ft_is_in_dico(possible_words, word))
		{
			std::cout << "Invalid word" << std::endl;
	
			continue;
		}
		tab[nb_tours] = ft_color_letters(word, hidden);
		if (hidden == word)
		{
			ft_print_display(tab);
			std::cout << GREENB << "\nCONGRATULATION : YOU WIN !!!!!!!" << RESET << std::endl;
			return ;
		}
		nb_tours++;
	}
	std::cout << REDB << "\nSorry : you lost! :(\nThe word was : " << hidden << "\nSee you sOoOn!!!"  << RESET << std::endl;
}





int main(int ac, char **av)
{
	std::ifstream				ifs;
	std::string					line;
	std::vector<std::string>	win_words;
	std::set<std::string>		possible_words;

	/* ************************************************************************** */
	/*					Put and check the dictionary in all words				  */
	/* ************************************************************************** */

	if (ac != 3)
	{
		std::cout << "Bad argument.\nTry that: First is possible word, second is win word" << std::endl;
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
		if (line.size() == 5 && !string_all_lower(line))
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

	ifs.open(av[1]);
	if (!ifs)
	{
		std::cout << "Bad dico" << std::endl;
		return (1);
	}
	while (getline(ifs, line))
	{
		if (line.size() == 5 && !string_all_lower(line))
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
