;;; DevNull- level 2

(day)                           ;; Sets daylight for this level. M
(set-track-name (_ "Get wet!"))         ;; The name of the levelM
(set-author "Francek") ;;
(start-time 110)                ;; We have two minutes to complete levelM
(set-start-position 237 249) ;; Where the player appearsM
(add-goal 237 241 #t "dn6")     ;; Where we should go (200,200) and whichlevel
                                ;; play when we are finished.M
(fog 0.7)

(if (= (difficulty) *hard*)
    (new-mr-black 237 250))
(if (= (difficulty) *hard*)
    (new-mr-black 237 248))
(if (= (difficulty) *hard*)
    (new-mr-black 236 250))
(if (= (difficulty) *hard*)
    (new-mr-black 236 248))
(if (= (difficulty) *normal*)
    (new-mr-black 237 250))
(if (= (difficulty) *normal*)
    (new-mr-black 236 248))

(add-teleport 237 231 237 249 0.3)
(define ff1 (forcefield 238.5 247.5 8.5 0.0 3.0 0.0 2.0 *ff-bounce*))
(define ff2 (forcefield 235.5 247.5 0.0 0.0 3.0 0.0 2.0 *ff-bounce*))
(define ff3 (forcefield 234.5 240.5 0.0 0.0 1.0 0.0 2.0 *ff-bounce*))
(define ff4 (forcefield 249.5 240.5 0.0 0.0 1.0 0.0 2.0 *ff-bounce*))
(forcefield 235.5 239.5 5.0 2.0 0.0 0.0 4.0 *ff-kill*) ;above the goal ;)
(forcefield 235.5 241.5 5.0 2.0 0.0 0.0 4.0 *ff-kill*) ;above the goal ;)


(switch 238 233
        (lambda() (set-onoff ff1 #t))
        (lambda()(set-onoff ff1 #f)))
(switch 238 244 ;; switch2 + cyclic platform
        (lambda() (set-onoff ff2 #t))
        (lambda()(set-onoff ff2 #f)))
(add-cyclic-platform 238 244 238 244 -11.5 6.0 0. 0.3)
(switch 232 249
        (lambda() (set-onoff ff3 #t))
        (lambda()(set-onoff ff3 #f)))
(switch 242 249
        (lambda() (set-onoff ff4 #t))
        (lambda()(set-onoff ff4 #f)))


(add-flag 239 249 300 #t 0.1)
(add-flag 242 247 300 #t 0.1)
(add-flag 237 240 200 #t 0.1)
(add-flag 237 242 200 #t 0.1)

(add-flag 240 249 300 #t 0.1)
(add-flag 242 246 300 #t 0.1)
(add-flag 241 249 300 #t 0.1)
(add-flag 242 245 300 #t 0.1)
