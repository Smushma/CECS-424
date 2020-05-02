% Days on which the objects were seen
day(tuesday).
day(wednesday).
day(thursday).
day(friday).

% The objects seen
object(balloon).
object(clothesline).
object(frisbee).
object(water_tower).

% Solver
solve :-
    % Initialize each person object and verify that each are different
    object(BarradaObject), object(GortObject), object(KlatuObject), object(NiktoObject),
    all_different([BarradaObject, GortObject, KlatuObject, NiktoObject]),
    
    % Initialize a day per person and verify that each are different
    day(BarradaDay), day(GortDay), day(KlatuDay), day(NiktoDay),
    all_different([BarradaDay, GortDay, KlatuDay, NiktoDay]),
    
    % Store the information in an array
    People = [ [ms_barrada, BarradaObject, BarradaDay],
               [ms_gort, GortObject, GortDay],
               [mr_klatu, KlatuObject, KlatuDay],
               [mr_nikto, NiktoObject, NiktoDay] ],
    
    % Cases that must be satisfied:
    % Case 1a: Mr. Klatu made his sighting at some point earlier in the week than the one who saw the balloon,
    \+ member([mr_klatu, balloon, _], People),
    \+ member([mr_klatu, _, friday], People),
    
    % Case 1b: but at some point later in the week than the one who spoted the Frisbee
    \+ member([mr_klatu, _, tuesday], People),
    \+ member([mr_klatu, frisbee, _], People),
    
    % Case 1c: (who isn't Ms. Gort.).
    \+ member([ms_gort, frisbee, _], People),
    
    % Case 2: Friday's sighting was made by either Ms.Barrada or the one who saw the clothesline (or both).
    (   (member([ms_barrada, _, friday], People));
    	(member([_, clothesline, friday], People));
    	(member([ms_barrada, clothesline, friday], People)) ),
    
    % Case 3: Mr.Nikto did not make his sighting on Tuesday.
    \+ member([mr_nikto, _, tuesday], People),
    
    % Case 4: Mr. Klatu isn't the one whose object turned out to be a water tower.
    \+ member([mr_klatu, water_tower, _], People),
    
    % Print the results
    print(ms_gort, GortObject, GortDay),
    print(mr_klatu, KlatuObject, KlatuDay),
    print(mr_nikto, NiktoObject, NiktoDay),
    print(ms_barrada, BarradaObject, BarradaDay).
    
% Succeed if all elements of the argument list are bound and different.
% Fail if any elements are unbound or equal to some other element.
all_different([H | T]) :- member(H, T), !, fail.        % (1)
all_different([_ | T]) :- all_different(T).             % (2)
all_different([_]).                                     % (3)

% Print out results
print(X, Y, Z) :-
    write(X), write(' saw a '), write(Y), write(' on ') , write(Z), write('.'), nl.