module gaussian_quadrature

  implicit none

contains

  pure subroutine get_standard_hermite_quadrature(npoints, z, w)

    integer, intent(in)    :: npoints
    real(8), intent(inout) :: z(:)
    real(8), intent(inout) :: w(:)

    z = 0.0d0
    w = 0.0d0

    if ((npoints .gt. 0) .and. (npoints .le. 5)) then

       if (npoints .eq. 1) then
          z = [0.0d0]
          w = [1.7724538509055159d0]
       else if (npoints .eq. 2) then
          z = [-0.7071067811865475d0,&
               &0.7071067811865475d0]
          w = [0.8862269254527579d0,&
               &0.8862269254527579d0]
       else if (npoints .eq. 3) then
          z = [-1.224744871391589d0,&
               &0.0d0,&
               &1.224744871391589d0]
          w = [0.2954089751509194d0,&
               &1.1816359006036772d0,&
               &0.2954089751509194d0]
       else if (npoints .eq. 4) then
          z = [-1.6506801238857847d0,&
               &-0.5246476232752904d0,&
               &0.5246476232752904d0,&
               &1.6506801238857847d0]
          w = [0.08131283544724519d0,&
               &0.8049140900055127d0,&
               &0.8049140900055127d0,&
               &0.08131283544724519d0]
       else if (npoints .eq. 5) then
          z = [-2.0201828704560856d0,&
               &-0.9585724646138185d0,&
               &0.0d0,&
               &0.9585724646138185d0,&
               &2.0201828704560856d0]
          w = [0.019953242059045917d0,&
               &0.3936193231522411d0,&
               &0.9453087204829418d0,&
               &0.3936193231522411d0,&
               &0.019953242059045917d0]
       end if

    else if ((npoints .gt. 5) .and. (npoints .le. 10)) then

       if (npoints .eq. 6) then
          z = [-2.3506049736744923d0,&
               &-1.335849074013697d0,&
               &-0.4360774119276165d0,&
               &0.4360774119276165d0,&
               &1.335849074013697d0,&
               &2.3506049736744923d0]
          w = [0.004530009905508835d0,&
               &0.15706732032285647d0,&
               &0.7246295952243924d0,&
               &0.7246295952243924d0,&
               &0.15706732032285647d0,&
               &0.004530009905508835d0]
       else if (npoints .eq. 7) then
          z = [-2.6519613568352334d0,&
               &-1.6735516287674714d0,&
               &-0.8162878828589646d0,&
               &0.0d0,&
               &0.8162878828589646d0,&
               &1.6735516287674714d0,&
               &2.6519613568352334d0]
          w = [0.0009717812450995199d0,&
               &0.05451558281912705d0,&
               &0.4256072526101278d0,&
               &0.8102646175568072d0,&
               &0.4256072526101278d0,&
               &0.05451558281912705d0,&
               &0.0009717812450995199d0]
       else if (npoints .eq. 8) then
          z = [-2.930637420257244d0,&
               &-1.981656756695843d0,&
               &-1.1571937124467802d0,&
               &-0.3811869902073221d0,&
               &0.3811869902073221d0,&
               &1.1571937124467802d0,&
               &1.981656756695843d0,&
               &2.930637420257244d0]
          w = [0.00019960407221136783d0,&
               &0.017077983007413467d0,&
               &0.20780232581489183d0,&
               &0.6611470125582415d0,&
               &0.6611470125582415d0,&
               &0.20780232581489183d0,&
               &0.017077983007413467d0,&
               &0.00019960407221136783d0]
       else if (npoints .eq. 9) then
          z = [-3.1909932017815277d0,&
               &-2.266580584531843d0,&
               &-1.468553289216668d0,&
               &-0.7235510187528376d0,&
               &0.0d0,&
               &0.7235510187528376d0,&
               &1.468553289216668d0,&
               &2.266580584531843d0,&
               &3.1909932017815277d0]
          w = [3.9606977263264365d-05,&
               &0.004943624275536941d0,&
               &0.08847452739437664d0,&
               &0.43265155900255564d0,&
               &0.720235215606051d0,&
               &0.43265155900255564d0,&
               &0.08847452739437664d0,&
               &0.004943624275536941d0,&
               &3.9606977263264365d-05]
       else if (npoints .eq. 10) then
          z = [-3.4361591188377374d0,&
               &-2.5327316742327897d0,&
               &-1.7566836492998816d0,&
               &-1.0366108297895136d0,&
               &-0.3429013272237046d0,&
               &0.3429013272237046d0,&
               &1.0366108297895136d0,&
               &1.7566836492998816d0,&
               &2.5327316742327897d0,&
               &3.4361591188377374d0]
          w = [7.640432855232641d-06,&
               &0.0013436457467812324d0,&
               &0.033874394455481106d0,&
               &0.2401386110823147d0,&
               &0.6108626337353258d0,&
               &0.6108626337353258d0,&
               &0.2401386110823147d0,&
               &0.033874394455481106d0,&
               &0.0013436457467812324d0,&
               &7.640432855232641d-06]
       end if

    end if

  end subroutine get_standard_hermite_quadrature

  pure subroutine get_standard_legendre_quadrature(npoints, z, w)

    integer, intent(in)    :: npoints
    real(8), intent(inout) :: z(:)
    real(8), intent(inout) :: w(:)

    z = 0.0d0
    w = 0.0d0

    if ((npoints .gt. 0) .and. (npoints .le. 5)) then

       if (npoints .eq. 1) then
          z = [0.0d0]
          w = [2.0d0]
       else if (npoints .eq. 2) then
          z = [-0.5773502691896257d0, &
               & 0.5773502691896257d0]
          w = [1.0d0, &
               & 1.0d0]
       else if (npoints .eq. 3) then
          z = [-0.7745966692414834d0,&
               &0.0d0,&
               &0.7745966692414834d0]
          w = [0.5555555555555557d0,&
               &0.8888888888888888d0,&
               &0.5555555555555557d0]
       else if (npoints .eq. 4) then
          z = [-0.8611363115940526d0,&
               &-0.33998104358485626d0,&
               &0.33998104358485626d0,&
               &0.8611363115940526d0]
          w = [0.3478548451374537d0,&
               &0.6521451548625462d0,&
               &0.6521451548625462d0,&
               &0.3478548451374537d0]
       else if (npoints .eq. 5) then
          z = [-0.906179845938664d0,&
               &-0.5384693101056831d0,&
               &0.0d0,&
               &0.5384693101056831d0,&
               &0.906179845938664d0]
          w = [0.23692688505618942d0,&
               &0.4786286704993662d0,&
               &0.568888888888889d0,&
               &0.4786286704993662d0,&
               &0.23692688505618942d0]
       end if

    else if ((npoints .gt. 5) .and. (npoints .le. 10)) then

       if (npoints .eq. 6) then
          z = [-0.932469514203152d0,&
               &-0.6612093864662645d0,&
               &-0.23861918608319693d0,&
               &0.23861918608319693d0,&
               &0.6612093864662645d0,&
               &0.932469514203152d0]
          w = [0.17132449237916975d0,&
               &0.36076157304813894d0,&
               &0.46791393457269137d0,&
               &0.46791393457269137d0,&
               &0.36076157304813894d0,&
               &0.17132449237916975d0]
       else if (npoints .eq. 7) then
          z = [-0.9491079123427585d0,&
               &-0.7415311855993945d0,&
               &-0.4058451513773972d0,&
               &0.0d0,&
               &0.4058451513773972d0,&
               &0.7415311855993945d0,&
               &0.9491079123427585d0]
          w = [0.12948496616887065d0,&
               &0.2797053914892766d0,&
               &0.3818300505051183d0,&
               &0.41795918367346896d0,&
               &0.3818300505051183d0,&
               &0.2797053914892766d0,&
               &0.12948496616887065d0]
       else if (npoints .eq. 8) then
          z = [-0.9602898564975362d0,&
               &-0.7966664774136267d0,&
               &-0.525532409916329d0,&
               &-0.18343464249564978d0,&
               &0.18343464249564978d0,&
               &0.525532409916329d0,&
               &0.7966664774136267d0,&
               &0.9602898564975362d0]
          w = [0.10122853629037669d0,&
               &0.22238103445337434d0,&
               &0.31370664587788705d0,&
               &0.36268378337836177d0,&
               &0.36268378337836177d0,&
               &0.31370664587788705d0,&
               &0.22238103445337434d0,&
               &0.10122853629037669d0]
       else if (npoints .eq. 9) then
          z = [-0.9681602395076261d0,&
               &-0.8360311073266358d0,&
               &-0.6133714327005904d0,&
               &-0.3242534234038089d0,&
               &0.0d0,&
               &0.3242534234038089d0,&
               &0.6133714327005904d0,&
               &0.8360311073266358d0,&
               &0.9681602395076261d0]
          w = [0.08127438836157472d0,&
               &0.18064816069485712d0,&
               &0.26061069640293566d0,&
               &0.3123470770400028d0,&
               &0.33023935500125967d0,&
               &0.3123470770400028d0,&
               &0.26061069640293566d0,&
               &0.18064816069485712d0,&
               &0.08127438836157472d0]
       else if (npoints .eq. 10) then
          z = [-0.9739065285171717d0,&
               &-0.8650633666889845d0,&
               &-0.6794095682990244d0,&
               &-0.4333953941292472d0,&
               &-0.14887433898163122d0,&
               &0.14887433898163122d0,&
               &0.4333953941292472d0,&
               &0.6794095682990244d0,&
               &0.8650633666889845d0,&
               &0.9739065285171717d0]
          w = [0.06667134430868807d0,&
               &0.14945134915058036d0,&
               &0.219086362515982d0,&
               &0.2692667193099965d0,&
               &0.295524224714753d0,&
               &0.295524224714753d0,&
               &0.2692667193099965d0,&
               &0.219086362515982d0,&
               &0.14945134915058036d0,&
               &0.06667134430868807d0]
       end if

    end if

  end subroutine get_standard_legendre_quadrature

  pure subroutine get_standard_laguerre_quadrature(npoints, z, w)

    integer, intent(in)    :: npoints
    real(8), intent(inout) :: z(:)
    real(8), intent(inout) :: w(:)

    z = 0.0d0
    w = 0.0d0

    if ((npoints .gt. 0) .and. (npoints .le. 5)) then

       if (npoints .eq. 1) then
          z = [1.0d0]
          w = [1.0d0]
       else if (npoints .eq. 2) then
          z = [0.585786437626905d0,&
               &3.414213562373095d0]
          w = [0.8535533905932737d0,&
               &0.14644660940672624d0]
       else if (npoints .eq. 3) then
          z = [0.4157745567834791d0,&
               &2.294280360279042d0,&
               &6.2899450829374794d0]
          w = [0.7110930099291729d0,&
               &0.278517733569241d0,&
               &0.010389256501586133d0]
       else if (npoints .eq. 4) then
          z = [0.3225476896193924d0,&
               &1.7457611011583465d0,&
               &4.536620296921128d0,&
               &9.395070912301133d0]
          w = [0.6031541043416337d0,&
               &0.35741869243779956d0,&
               &0.038887908515005405d0,&
               &0.0005392947055613296d0]
       else if (npoints .eq. 5) then
          z = [0.26356031971814087d0,&
               &1.4134030591065168d0,&
               &3.596425771040722d0,&
               &7.085810005858837d0,&
               &12.640800844275782d0]
          w = [0.5217556105828085d0,&
               &0.398666811083176d0,&
               &0.07594244968170769d0,&
               &0.0036117586799220545d0,&
               &2.3369972385776248d-05]
       end if

    else if ((npoints .gt. 5) .and. (npoints .le. 10)) then

       if (npoints .eq. 6) then
          z = [0.2228466041792607d0,&
               &1.1889321016726226d0,&
               &2.992736326059314d0,&
               &5.77514356910451d0,&
               &9.83746741838259d0,&
               &15.982873980601703d0]
          w = [0.45896467394996476d0,&
               &0.41700083077212d0,&
               &0.11337338207404488d0,&
               &0.010399197453149087d0,&
               &0.00026101720281493265d0,&
               &8.985479064296213d-07]
       else if (npoints .eq. 7) then
          z = [0.19304367656036225d0,&
               &1.0266648953391924d0,&
               &2.567876744950746d0,&
               &4.900353084526484d0,&
               &8.18215344456286d0,&
               &12.734180291797815d0,&
               &19.39572786226254d0]
          w = [0.40931895170127336d0,&
               &0.4218312778617202d0,&
               &0.1471263486575053d0,&
               &0.020633514468716942d0,&
               &0.001074010143280746d0,&
               &1.5865464348564196d-05,&
               &3.1703154789955624d-08]
       else if (npoints .eq. 8) then
          z = [0.17027963230510093d0,&
               &0.90370177679938d0,&
               &2.251086629866131d0,&
               &4.266700170287659d0,&
               &7.0459054023934655d0,&
               &10.758516010180996d0,&
               &15.740678641278004d0,&
               &22.863131736889265d0]
          w = [0.36918858934163495d0,&
               &0.4187867808143447d0,&
               &0.17579498663717255d0,&
               &0.033343492261215794d0,&
               &0.0027945362352256834d0,&
               &9.076508773358139d-05,&
               &8.48574671627257d-07,&
               &1.0480011748715153d-09]
       else if (npoints .eq. 9) then
          z = [0.1523222277318084d0,&
               &0.8072200227422562d0,&
               &2.005135155619347d0,&
               &3.783473973331233d0,&
               &6.204956777876613d0,&
               &9.372985251687576d0,&
               &13.466236911092095d0,&
               &18.833597788991696d0,&
               &26.374071890927375d0]
          w = [0.33612642179796287d0,&
               &0.4112139804239856d0,&
               &0.1992875253708841d0,&
               &0.04746056276565138d0,&
               &0.005599626610794551d0,&
               &0.00030524976709320943d0,&
               &6.592123026075329d-06,&
               &4.1107693303495754d-08,&
               &3.290874030350679d-11]
       else if (npoints .eq. 10) then
          z = [0.1377934705404926d0,&
               &0.729454549503171d0,&
               &1.8083429017403159d0,&
               &3.4014336978548996d0,&
               &5.552496140063804d0,&
               &8.330152746764497d0,&
               &11.843785837900066d0,&
               &16.279257831378104d0,&
               &21.99658581198076d0,&
               &29.92069701227389d0]
          w = [0.3084411157650173d0,&
               &0.4011199291552761d0,&
               &0.2180682876118096d0,&
               &0.062087456098677773d0,&
               &0.0095015169751811d0,&
               &0.0007530083885875384d0,&
               &2.8259233495995642d-05,&
               &4.249313984962698d-07,&
               &1.839564823979633d-09,&
               &9.91182721960906d-13]
       end if

    end if

  end subroutine get_standard_laguerre_quadrature

end module gaussian_quadrature

subroutine test_weights(npoints)

  use gaussian_quadrature

  real(8) :: z(npoints), w(npoints)

  call get_standard_hermite_quadrature(npoints, z, w)
  !print *, z 
  print *, sum(w)/sqrt(4.0d0*atan(1.0d0))

  call get_standard_legendre_quadrature(npoints, z, w)
  !print *, z 
  print *, sum(w)/2.0

  call get_standard_laguerre_quadrature(npoints, z, w)
  !print *, z 
  print *, sum(w)
  
end subroutine test_weights

program main

  integer, parameter :: npoints = 10
  integer :: n

  do n = 1, npoints
     call test_weights(n)
  end do

end program main
