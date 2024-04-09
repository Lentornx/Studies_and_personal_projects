-- querry 1: podaj zestawienie ksiązek, których ilość zamówiona nie zgadza się z ilością dostarczoną, a które zostały sprzedane w ilości 
-- conajmniej X sztuk, wraz z ilością brakujących egzemplarzy
-- scenariusz: księgarnia chce domówić brakujące egzemplarze książek, które są ostatnio w dużym obrocie

	SELECT K.ISBN, K.Tytul, SumyZamowionych.SumaIlosciZamowionych - SumyDostarczonych.SumaIlosciDostarczonych AS roznica, SUM(PS.Ilosc) AS ile_sprzedanych 
	FROM Ksiazki K
	JOIN Pozycje_sprzedazy PS ON PS.Kupiona_ksiazka = K.ISBN
	JOIN (
	   SELECT K.ISBN AS ISBN, SUM(PD.Ilosc_dostarczona) AS SumaIlosciDostarczonych
	   FROM Ksiazki K
	   JOIN Pozycje_zamowien PZ ON K.ISBN = PZ.Zamowiona_ksiazka
	   JOIN Pozycje_Dostawy PD ON PZ.Id = PD.Nr_wypelnianej_pozycji
	   GROUP BY K.ISBN, K.Tytul
	) SumyDostarczonych ON K.ISBN = SumyDostarczonych.ISBN

	JOIN (
	   SELECT K.ISBN AS ISBN, SUM(PZ.Ilosc_zamowiona) AS SumaIlosciZamowionych
	   FROM Ksiazki K
	   JOIN Pozycje_zamowien PZ ON K.ISBN = PZ.Zamowiona_ksiazka
	   JOIN Zamowienia Z ON PZ.Nr_zamowienia = Z.Id
	   WHERE Z.Stan = 'dostarczone'
	   GROUP BY K.ISBN, K.Tytul
	) SumyZamowionych ON SumyZamowionych.ISBN = SumyDostarczonych.ISBN

	WHERE SumyDostarczonych.SumaIlosciDostarczonych <> SumyZamowionych.SumaIlosciZamowionych
	GROUP BY K.ISBN, K.Tytul, SumyZamowionych.SumaIlosciZamowionych, SumyDostarczonych.SumaIlosciDostarczonych
	HAVING SUM(PS.Ilosc) > 0

-- querry 2: podaj zestawienie hurtowni, które nie wypełniły poprawnie zamówień więcej niż raz
-- scenariusz: księgarnia planuje zakończyć współpracę z zawodnymi hurtowniami

SELECT H.Id, H.Nazwa, COUNT(*) AS Ilosc_niepoprawnosci
FROM Hurtownie H
JOIN Zamowienia Z ON H.Id = Z.Wykonawca
JOIN Pozycje_zamowien PZ ON Z.Id = PZ.Nr_zamowienia
JOIN (
   SELECT PD.Nr_wypelnianej_pozycji, SUM(PD.Ilosc_dostarczona) AS SumaIlosciDostarczonych
   FROM Pozycje_Dostawy PD
   GROUP BY PD.Nr_wypelnianej_pozycji
) SumyDostarczonych ON PZ.Id = SumyDostarczonych.Nr_wypelnianej_pozycji
WHERE PZ.Ilosc_zamowiona <> SumyDostarczonych.SumaIlosciDostarczonych 
GROUP BY H.Id, H.Nazwa
HAVING  COUNT(*) > 1


-- querry 3: podaj zestawienie hurtowni, której średni czas dostawy od zamówienia wynosi mniej niż X dni, oraz nigdy nie anulowała swojej dostawy
-- scenariusz: księgarnia planuje zacieśnić współpracę z hurtowniami zapewniającymi szybkie, niezawodne dostawy

SELECT H.Id, H.Nazwa, AVG(DATEDIFF(DAY, Z.Data_zlozenia, D.Data_przyjecia)) AS SredniCzasDostawy
FROM Hurtownie H   
JOIN Zamowienia Z ON H.Id = Z.Wykonawca
JOIN Pozycje_zamowien PZ ON Z.Id = PZ.Nr_zamowienia
JOIN Pozycje_Dostawy PD ON  PZ.Id = PD.Nr_wypelnianej_pozycji
JOIN DOSTAWY D ON PD.Nr_dostawy = D.Id
WHERE
    Z.Stan <> 'anulowane'
GROUP BY H.Id, H.Nazwa
HAVING
    AVG(DATEDIFF(DAY, Z.Data_zlozenia, D.Data_przyjecia)) < 5;

-- querry 4: podaj zestawienie książek ze względu na łączny zysk w przeciągu roku, sortując malejąco
-- scenariusz: księgarnia potrzebuje informacji, które książki przyniosł największe zyski

SELECT K.ISBN, K.Tytul,
	CAST(SUM((PS.Cena_jednostkowa - Cena_zam.SredniaCena) * PS.Ilosc - PS.Rabat) AS DECIMAL(5,2)) AS LacznyZysk
FROM Ksiazki K
JOIN Pozycje_sprzedazy PS ON K.ISBN = PS.Kupiona_ksiazka
JOIN Sprzedaze S ON PS.Nr_sprzedazy = S.Id
	JOIN (
		SELECT K.ISBN AS ISBN, K.Tytul, ROUND(AVG(PZ.Cena),2) AS SredniaCena
		FROM Ksiazki K
		JOIN Pozycje_zamowien PZ ON K.ISBN = PZ.Zamowiona_ksiazka
		GROUP BY K.ISBN, K.Tytul
		) Cena_zam ON K.ISBN = Cena_zam.ISBN
WHERE YEAR(S.Data_sprzedazy) = 2023
GROUP BY K.ISBN, K.Tytul
ORDER BY LacznyZysk DESC;
	
-- querry 5: podaj zestawienie autorów, których książki w danym roku sprzedały się w ilości większej niż X, wraz z ilością sprzedanych egzemplarzy
-- Scenariusz: księgarnia planuje dokonać zamówień książek pisarzy, których inne tytuły dobrze się sprzedały

	SELECT A.Id, A.Imie, A.Nazwisko, SUM(PS.Ilosc) AS SumaSprzedanychKsiazek
	FROM Autorzy A
	JOIN Autorzy_ksiazek AK ON A.Id = AK.Autor
	JOIN Ksiazki K ON AK.Ksiazka = K.ISBN
	JOIN Pozycje_sprzedazy PS ON K.ISBN = PS.Kupiona_ksiazka
	JOIN Sprzedaze S ON PS.Nr_sprzedazy = S.Id
	WHERE YEAR(S.Data_sprzedazy) = 2023
	GROUP BY A.Id, A.Imie, A.Nazwisko
	HAVING SUM(PS.Ilosc) > 10;

-- querry 6: podaj zestawienie książek posegregowanych rosnąco, ze względu na ilość zakupionych sztuk
-- scenariusz: księgarnia planuje nałożyć rabaty na książki, które kiepsko się sprzedają

DROP VIEW IF EXISTS TopSellingBooksView;
GO
	CREATE VIEW TopSellingBooksView AS
SELECT K.ISBN, K.Tytul, SUM(PS.Ilosc) AS Ilosc_sprzedanych_sztuk
FROM Ksiazki K
JOIN Pozycje_sprzedazy PS ON K.ISBN = PS.Kupiona_ksiazka
GROUP BY K.ISBN, K.Tytul;
GO
	SELECT *
FROM TopSellingBooksView
ORDER BY Ilosc_sprzedanych_sztuk;

-- querry 7: podaj książki, które zostały kupione w kilku sztukach naraz conajmniej X razy
-- scenariusz: Księgarnia chce nałożyć żniżki przy kupowaniu kilku kopii tych samych książek
-- i chce wiedzieć, na sprzedaż których egzemplarzy może to najbardziej wpłynąć

SELECT K.ISBN, K.Tytul, COUNT(*) AS ile_razy_kupione_X_na_raz
FROM Ksiazki K
JOIN Pozycje_sprzedazy PS ON K.ISBN = PS.Kupiona_ksiazka
WHERE PS.Ilosc > 1
GROUP BY K.ISBN, K.Tytul
HAVING COUNT(*) >= 3
ORDER BY ile_razy_kupione_X_na_raz DESC;