#include <stdio.h>
int Health(float Ax,float Ay,float Az,float Gx,float Gy,float Gz );
int main(){
    //-0.13	-0.96	-0.31	-213.53	-25.9	-34.04

	printf("%d\n",Health(-0.13,-0.96,-0.31,-213.53,-25.9,-34.04));
    return 0;
}
int Health(float Ax,float Ay,float Az,float Gx,float Gy,float Gz)
{
  float AxXGx = Ax * Gx, AyXAz = Ay * Az, AxXGy = Ax * Gy, AxXGz = Ax * Gz, AxXAy = Ax * Ay, AxXAz = Ax * Az, AyXAx = Ay * Ax, AyXGx = Ay * Gx, AyXGy = Ay * Gy, AyXGz = Ay * Gz, AzXAx = Az * Ax, AzXAy = Az * Ay, AzXGx = Az * Gx, AzxGy = Az * Gy, AzXGz = Az * Gz, Ax_squared = Ax * Ax, Ay_squared = Ay * Ay, Az_squared = Az * Az, Gx_squared = Gx * Gx, Gy_squared = Gy * Gy, Gz_squared = Gz * Gz, GxXGz = Gx * Gz, GxXGy = Gx * Gy, GyXGz = Gy * Gz, AzXGy = Az * Gy;
  if ( Gz_squared <= -0.12) {
		if ( Az <= 0.73) {
			if ( Ay <= -0.64) {
				if ( AxXAy <= -0.08) {
					if ( Ay_squared <= -0.06) {
						if ( AyXGy <= 0.16) {
							if ( AyXAz <= 0.2) {
								if ( AxXAy <= -0.68) {
									if ( AxXGx <= 0.09) {
										if ( GyXGz <= -0.02) {
											if ( AxXAy <= -1.03) {
												return 1;
											}
											else {
												if ( AxXGy <= -0.08) {
													return 1;
												}
												else {
													if ( Gy_squared <= -0.11) {
														if ( AzXGx <= 0.01) {
															return 1;
														}
														else {
															if ( AxXGz <= -0.07) {
																return 0;
															}
															else {
																if ( AyXGy <= -0.08) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( GxXGz <= 0.01) {
												if ( AzXGx <= 0.01) {
													return 1;
												}
												else {
													if ( AyXAz <= 0.16) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Gz <= 0.05) {
											if ( Gx <= 0.43) {
												if ( Gz_squared <= -0.14) {
													return 1;
												}
												else {
													if ( AxXAz <= -0.02) {
														if ( Gy <= 0.1) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( Gx_squared <= -0.08) {
										if ( AyXGz <= 0.16) {
											if ( AxXGz <= -0.04) {
												if ( GxXGy <= 0.01) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												if ( GxXGz <= 0.0) {
													return 0;
												}
												else {
													if ( AzXGy <= -0.06) {
														return 2;
													}
													else {
														if ( AzXGy <= -0.02) {
															return 0;
														}
														else {
															if ( AzXGx <= 0.02) {
																return 2;
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( Gx_squared <= -0.11) {
									if ( Gz <= 0.01) {
										if ( GyXGz <= -0.04) {
											if ( Gy_squared <= -0.13) {
												if ( Gz <= -0.37) {
													return 1;
												}
												else {
													if ( AyXGx <= -0.01) {
														if ( AyXGx <= -0.06) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( Gx <= 0.05) {
													return 1;
												}
												else {
													if ( AyXAz <= 0.66) {
														if ( AzXGy <= -0.22) {
															if ( Ax_squared <= -0.0) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( GxXGz <= 0.01) {
												if ( AxXAz <= -0.15) {
													if ( AzXGz <= 0.03) {
														if ( AxXGx <= 0.09) {
															if ( Ay_squared <= -0.1) {
																if ( GxXGz <= 0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( Gx_squared <= -0.14) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXAz <= 0.85) {
															if ( AzXGy <= 0.01) {
																if ( AxXGz <= -0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGy <= 0.06) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Az_squared <= -0.04) {
														if ( Gy_squared <= -0.16) {
															if ( Gy_squared <= -0.16) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															if ( GxXGz <= 0.01) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( Ay <= -0.65) {
															if ( Gz <= -0.03) {
																if ( Gz_squared <= -0.14) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( GxXGy <= 0.01) {
											if ( Gy <= -0.09) {
												if ( GyXGz <= -0.03) {
													return 0;
												}
												else {
													return 2;
												}
											}
											else {
												if ( AxXAz <= -0.2) {
													if ( Gy_squared <= -0.16) {
														if ( AxXAz <= -0.24) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														if ( GxXGy <= -0.05) {
															return 1;
														}
														else {
															if ( Gy <= -0.05) {
																return 0;
															}
															else {
																if ( AxXGy <= 0.09) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( AxXGx <= 0.02) {
														if ( Az <= -0.53) {
															return 0;
														}
														else {
															if ( AxXGx <= 0.0) {
																if ( AzXGx <= 0.09) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( GyXGz <= -0.0) {
												if ( AxXAy <= -0.52) {
													if ( AxXGy <= 0.1) {
														if ( AxXGy <= -0.05) {
															return 1;
														}
														else {
															if ( AzXGx <= 0.05) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXGz <= -0.07) {
														return 1;
													}
													else {
														if ( AxXAz <= -0.06) {
															if ( Gy_squared <= -0.16) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.07) {
										if ( Gz <= -0.03) {
											if ( AxXAz <= -0.07) {
												if ( GxXGz <= 0.0) {
													return 0;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gy <= 0.15) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
									else {
										return 2;
									}
								}
							}
						}
						else {
							if ( Gx <= 0.65) {
								if ( AyXGy <= 0.29) {
									if ( Gx <= -0.4) {
										return 2;
									}
									else {
										if ( AzXGz <= 0.02) {
											if ( Gx <= -0.15) {
												return 0;
											}
											else {
												if ( GxXGz <= 0.01) {
													return 2;
												}
												else {
													if ( Az <= -0.2) {
														return 2;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( AyXGx <= -0.13) {
												return 1;
											}
											else {
												if ( Az <= -0.2) {
													return 1;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
								else {
									if ( Gy <= -1.36) {
										return 2;
									}
									else {
										if ( AxXAz <= -0.17) {
											if ( Ay_squared <= -0.08) {
												if ( AyXGx <= -0.27) {
													return 0;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( Gz_squared <= -0.13) {
												if ( Gy_squared <= -0.09) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( AxXGz <= -0.06) {
									return 2;
								}
								else {
									if ( AzXGy <= 0.23) {
										return 1;
									}
									else {
										if ( Gy_squared <= 0.21) {
											if ( AyXGy <= 0.73) {
												return 1;
											}
											else {
												if ( AyXGx <= -0.48) {
													return 1;
												}
												else {
													if ( Az_squared <= 0.04) {
														if ( AzXGy <= 0.33) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 1;
										}
									}
								}
							}
						}
					}
					else {
						if ( AxXGy <= -0.13) {
							if ( Ay_squared <= 0.04) {
								if ( GxXGy <= -0.16) {
									if ( GxXGy <= -0.34) {
										return 2;
									}
									else {
										if ( Gz <= -0.26) {
											return 2;
										}
										else {
											if ( AxXGz <= 0.05) {
												if ( AzXGz <= 0.01) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( AxXGy <= -0.27) {
										if ( GxXGz <= -0.01) {
											return 2;
										}
										else {
											return 2;
										}
									}
									else {
										if ( GxXGy <= 0.06) {
											if ( AyXAz <= 0.13) {
												return 1;
											}
											else {
												if ( AxXGx <= -0.07) {
													return 1;
												}
												else {
													if ( GxXGy <= -0.02) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( Gx_squared <= 0.32) {
									if ( AyXGy <= 0.97) {
										if ( AxXGx <= -0.18) {
											return 2;
										}
										else {
											if ( Ay_squared <= 0.13) {
												if ( AyXGy <= 0.8) {
													if ( AxXAz <= 0.01) {
														if ( AxXGy <= -0.22) {
															if ( Az <= 0.37) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( GxXGy <= -0.04) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AzXGy <= 0.02) {
													return 2;
												}
												else {
													if ( AxXGy <= -0.25) {
														if ( AxXGz <= 0.0) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														if ( Gz <= -0.06) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
									else {
										if ( AxXGx <= 0.46) {
											if ( Gx <= 1.03) {
												if ( AyXGx <= -0.46) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									return 2;
								}
							}
						}
						else {
							if ( AxXAz <= -0.05) {
								if ( Ax_squared <= 0.1) {
									if ( AyXGz <= 0.01) {
										if ( AxXGx <= -0.01) {
											if ( Gx_squared <= -0.15) {
												return 0;
											}
											else {
												if ( AyXGx <= 0.16) {
													if ( Gy_squared <= -0.16) {
														if ( GyXGz <= -0.02) {
															if ( GxXGy <= 0.01) {
																if ( Gy_squared <= -0.16) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AxXGx <= -0.04) {
															if ( AxXGz <= 0.02) {
																return 0;
															}
															else {
																if ( GxXGz <= 0.0) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXAz <= 0.53) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AzXGy <= -0.44) {
														return 0;
													}
													else {
														if ( AxXAy <= -0.51) {
															return 2;
														}
														else {
															if ( AzXGx <= 0.11) {
																return 0;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( Gz_squared <= -0.14) {
												if ( GxXGy <= -0.03) {
													return 0;
												}
												else {
													if ( Ax <= 0.74) {
														if ( AzXGz <= -0.02) {
															return 2;
														}
														else {
															if ( AyXGy <= 0.17) {
																if ( Gy <= 0.12) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AzXGz <= -0.06) {
													if ( AxXAy <= -0.28) {
														if ( AzXGy <= 0.09) {
															if ( GxXGz <= 0.01) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXAy <= -0.22) {
															return 0;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AzXGy <= -0.13) {
														return 2;
													}
													else {
														if ( AyXGz <= -0.03) {
															if ( AxXGx <= 0.11) {
																if ( Gx_squared <= -0.13) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
									else {
										if ( AyXAz <= 0.62) {
											if ( AxXGy <= 0.03) {
												if ( AxXAy <= -0.42) {
													if ( AzXGx <= 0.07) {
														if ( AxXGy <= -0.04) {
															if ( AyXAz <= 0.22) {
																return 1;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AxXGz <= -0.0) {
														if ( Gx <= 0.13) {
															if ( GxXGz <= 0.02) {
																if ( AzXGx <= 0.09) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGy <= -0.04) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Ay <= -0.73) {
													if ( AxXGz <= -0.1) {
														return 2;
													}
													else {
														if ( GyXGz <= -0.07) {
															return 0;
														}
														else {
															if ( AxXGx <= -0.09) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( Gx <= 0.37) {
														if ( AxXAz <= -0.14) {
															return 1;
														}
														else {
															if ( GxXGz <= 0.01) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AxXGz <= -0.07) {
												return 2;
											}
											else {
												if ( AzXGx <= -0.21) {
													return 2;
												}
												else {
													if ( AyXAz <= 0.81) {
														if ( GxXGz <= 0.01) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
								}
								else {
									if ( Ay_squared <= 0.06) {
										if ( Gx_squared <= -0.11) {
											if ( GxXGz <= 0.01) {
												if ( AxXGx <= 0.09) {
													if ( AyXAz <= 0.56) {
														if ( Gx <= -0.42) {
															return 2;
														}
														else {
															if ( GyXGz <= -0.02) {
																if ( GxXGz <= 0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXGz <= 0.21) {
														if ( GyXGz <= -0.02) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gx <= 0.42) {
											if ( AxXAz <= -0.22) {
												if ( AxXGz <= -0.04) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												if ( AxXGz <= -0.14) {
													return 1;
												}
												else {
													if ( AyXGy <= -0.34) {
														return 2;
													}
													else {
														if ( GxXGz <= 0.01) {
															return 1;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( GxXGy <= 0.01) {
									if ( AyXGz <= 0.02) {
										if ( AyXGx <= 0.24) {
											if ( AxXGz <= 0.13) {
												if ( AzXGy <= -0.01) {
													if ( GxXGz <= 0.01) {
														if ( AyXGx <= 0.07) {
															if ( GxXGz <= 0.0) {
																return 1;
															}
															else {
																if ( Gx_squared <= -0.15) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GxXGy <= -0.01) {
																return 0;
															}
															else {
																if ( AxXGz <= 0.05) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( Az_squared <= -0.2) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( GxXGy <= 0.0) {
														if ( GxXGz <= 0.02) {
															if ( Ay_squared <= 0.24) {
																if ( AzXGy <= 0.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AxXAy <= -0.5) {
															return 0;
														}
														else {
															if ( AyXGx <= -0.02) {
																if ( AzXGx <= 0.0) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Ay <= -0.86) {
												return 2;
											}
											else {
												if ( AzXGx <= 0.05) {
													return 0;
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( Gy_squared <= -0.16) {
											if ( AyXGz <= 0.07) {
												if ( Gx <= 0.17) {
													if ( GxXGy <= 0.01) {
														if ( AxXAy <= -0.66) {
															return 1;
														}
														else {
															if ( GxXGy <= 0.01) {
																if ( AzXGz <= 0.02) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AyXAz <= 0.17) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AzXGy <= -0.01) {
													if ( Ay_squared <= 0.18) {
														if ( Gx <= 0.0) {
															if ( Gz_squared <= -0.14) {
																return 2;
															}
															else {
																if ( AzXGy <= -0.02) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXGy <= 0.02) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( Ay_squared <= 0.18) {
												if ( Ax <= 1.11) {
													if ( AzXGy <= 0.02) {
														if ( AxXGy <= 0.05) {
															if ( Ay <= -0.75) {
																return 0;
															}
															else {
																if ( AzXGz <= 0.04) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXGy <= 0.06) {
																return 2;
															}
															else {
																if ( AyXGy <= -0.78) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Az <= 0.41) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
								else {
									if ( Ay <= -0.81) {
										if ( Gx_squared <= -0.12) {
											if ( AyXGx <= 0.18) {
												if ( AxXAz <= -0.02) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( GxXGz <= 0.04) {
												return 2;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( GxXGz <= 0.01) {
											if ( Gx_squared <= -0.11) {
												if ( GxXGy <= 0.04) {
													if ( AxXGz <= -0.02) {
														if ( AxXGy <= 0.02) {
															if ( GxXGz <= 0.01) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															if ( GxXGy <= 0.02) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AzXGz <= -0.02) {
															return 1;
														}
														else {
															if ( AxXGx <= -0.06) {
																return 1;
															}
															else {
																if ( AzXGx <= 0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													if ( Az_squared <= -0.19) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AzXGx <= 0.09) {
												if ( Gz_squared <= -0.13) {
													if ( Gy_squared <= -0.15) {
														if ( AyXAz <= 0.21) {
															if ( Gy_squared <= -0.16) {
																return 0;
															}
															else {
																if ( AxXAz <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXAz <= 0.32) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( GxXGy <= 0.05) {
															return 1;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AyXAz <= 0.08) {
														return 2;
													}
													else {
														if ( AzXGz <= 0.08) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( Az <= -0.24) {
						if ( Az <= -0.6) {
							if ( AyXGy <= 0.03) {
								if ( Ay <= -0.67) {
									if ( AxXAy <= 0.06) {
										if ( GyXGz <= -0.02) {
											return 2;
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gy <= 0.15) {
											if ( AxXAy <= 0.17) {
												return 2;
											}
											else {
												return 1;
											}
										}
										else {
											if ( Ay <= -0.75) {
												if ( Gx_squared <= -0.13) {
													return 1;
												}
												else {
													if ( AxXGx <= 2.46) {
														if ( Gx_squared <= 0.02) {
															return 2;
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GxXGz <= 0.0) {
													return 1;
												}
												else {
													if ( AyXAz <= 0.64) {
														return 0;
													}
													else {
														if ( Gy <= 0.4) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( Gy_squared <= -0.13) {
										if ( GxXGz <= 0.02) {
											if ( GyXGz <= -0.04) {
												return 0;
											}
											else {
												if ( AzXGz <= -0.1) {
													return 0;
												}
												else {
													if ( Gx <= -0.0) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AzXGy <= -0.39) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								if ( AxXAz <= 0.09) {
									if ( Ay <= -0.67) {
										if ( Az_squared <= 0.09) {
											if ( AxXGx <= -0.02) {
												return 2;
											}
											else {
												if ( AyXAz <= 0.74) {
													if ( GyXGz <= -0.03) {
														if ( AyXGy <= 0.09) {
															return 1;
														}
														else {
															if ( AxXGz <= -0.01) {
																return 2;
															}
															else {
																if ( AxXAy <= 0.02) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( Gx <= 0.71) {
												if ( GxXGz <= 0.0) {
													if ( Ay_squared <= -0.03) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( Az <= -0.78) {
														if ( Gz <= 0.09) {
															if ( AyXGy <= 0.26) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( GyXGz <= -0.04) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( GxXGz <= 0.0) {
											return 1;
										}
										else {
											if ( AzXGy <= 0.43) {
												if ( GxXGy <= 0.0) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AyXAz <= 0.71) {
										if ( AxXGz <= -0.02) {
											if ( Gz <= 0.13) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AzXGx <= -0.3) {
											return 1;
										}
										else {
											if ( AxXAz <= 0.16) {
												if ( AyXAz <= 0.86) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
						else {
							if ( AxXAz <= 0.05) {
								if ( AyXGz <= 0.13) {
									if ( Ay_squared <= 0.13) {
										if ( GxXGz <= 0.01) {
											if ( Gy_squared <= -0.16) {
												if ( AyXGx <= -0.08) {
													return 1;
												}
												else {
													if ( AyXGy <= 0.07) {
														if ( Ay <= -0.72) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AzXGy <= 0.29) {
													if ( Gx_squared <= -0.12) {
														if ( AzXGz <= -0.09) {
															return 1;
														}
														else {
															if ( Gz_squared <= -0.14) {
																return 1;
															}
															else {
																if ( Gz_squared <= -0.14) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( Az <= -0.49) {
												if ( Gx <= 0.12) {
													return 0;
												}
												else {
													if ( Gy <= -0.03) {
														return 2;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AzXGz <= -0.06) {
													if ( GxXGy <= 0.0) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( GxXGy <= -0.01) {
														return 1;
													}
													else {
														if ( GxXGy <= 0.0) {
															if ( Ay <= -0.7) {
																if ( AxXAz <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGy <= 0.1) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Gy_squared <= -0.02) {
											if ( GxXGy <= 0.02) {
												if ( Gx <= 0.42) {
													if ( AyXAz <= 0.58) {
														return 1;
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AzXGy <= -0.24) {
										return 1;
									}
									else {
										if ( AzXGx <= 0.11) {
											if ( AzXGz <= 0.13) {
												if ( AyXAz <= 0.61) {
													if ( AyXAz <= 0.51) {
														return 2;
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( AyXGz <= 0.14) {
									if ( Gy_squared <= -0.06) {
										if ( AxXGy <= 0.0) {
											if ( Az <= -0.31) {
												if ( AzXGy <= -0.26) {
													return 1;
												}
												else {
													if ( Ay <= -0.75) {
														if ( Ay_squared <= 0.18) {
															if ( AyXGx <= 0.06) {
																if ( AzXGz <= -0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( GyXGz <= -0.04) {
															return 1;
														}
														else {
															if ( AxXAz <= 0.11) {
																if ( GxXGy <= -0.02) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXAy <= 0.31) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AzXGz <= -0.04) {
													if ( AzXGy <= 0.06) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGy <= -0.01) {
														if ( AzXGx <= 0.09) {
															if ( Gx_squared <= -0.09) {
																if ( Gx <= 0.12) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXGx <= -0.07) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( AxXAy <= 0.54) {
												if ( Ay <= -0.69) {
													if ( GxXGy <= -0.01) {
														if ( Az <= -0.49) {
															return 1;
														}
														else {
															if ( Gx <= 0.71) {
																if ( AxXGy <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( GyXGz <= -0.03) {
															if ( AyXGz <= -0.13) {
																return 1;
															}
															else {
																if ( AxXGx <= -0.0) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GxXGy <= 0.03) {
																if ( AxXAy <= 0.4) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( GxXGz <= 0.0) {
														return 2;
													}
													else {
														if ( Gy <= -0.29) {
															return 1;
														}
														else {
															if ( Gx <= 0.12) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( Gx_squared <= -0.14) {
											return 2;
										}
										else {
											if ( AxXAy <= 0.32) {
												if ( AyXGy <= 0.75) {
													return 2;
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( Gz <= -0.43) {
										return 2;
									}
									else {
										if ( Gy_squared <= 0.01) {
											if ( AzXGx <= -0.07) {
												return 1;
											}
											else {
												if ( Gy <= -0.21) {
													return 1;
												}
												else {
													if ( Ay_squared <= 0.11) {
														return 0;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
						}
					}
					else {
						if ( Gy_squared <= -0.12) {
							if ( AzXGx <= -0.01) {
								if ( Gx <= 0.66) {
									if ( AyXGy <= 0.07) {
										if ( AzXGz <= 0.01) {
											if ( AxXAy <= 0.05) {
												if ( AyXAz <= 0.38) {
													if ( AxXGx <= 0.02) {
														if ( AzXGy <= -0.04) {
															if ( GxXGz <= 0.01) {
																return 0;
															}
															else {
																if ( Gx <= 0.39) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXGx <= -0.09) {
																if ( AxXGx <= 0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXGy <= 0.01) {
															if ( Gy <= 0.31) {
																if ( AzXGz <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AxXAy <= 0.02) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GxXGy <= 0.01) {
													if ( AzXGy <= -0.01) {
														if ( AxXGz <= -0.02) {
															return 1;
														}
														else {
															if ( AxXGz <= -0.01) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXGy <= 0.04) {
															if ( AyXGy <= 0.04) {
																if ( Gy <= 0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXAz <= 0.26) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AyXGx <= -0.19) {
														if ( Ay_squared <= -0.06) {
															return 1;
														}
														else {
															if ( AyXGz <= -0.09) {
																if ( AzXGz <= -0.05) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AzXGy <= -0.05) {
															if ( GyXGz <= -0.01) {
																if ( AxXGy <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAy <= 0.22) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AxXAz <= 0.09) {
																if ( GyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXAz <= 0.17) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
										}
										else {
											if ( AxXGz <= -0.0) {
												if ( Az <= 0.41) {
													if ( Gy <= 0.42) {
														if ( Az <= -0.09) {
															if ( AxXGx <= -0.0) {
																if ( Gy <= 0.16) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXGy <= 0.04) {
																if ( Az <= 0.19) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXAz <= 0.27) {
													return 0;
												}
												else {
													if ( Az <= -0.13) {
														return 0;
													}
													else {
														if ( AyXAz <= 0.34) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
											}
										}
									}
									else {
										if ( AyXAz <= 0.25) {
											if ( GyXGz <= -0.02) {
												if ( AxXAy <= 0.37) {
													if ( GyXGz <= -0.03) {
														if ( Gx <= 0.28) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Gz_squared <= -0.14) {
												if ( AyXAz <= 0.41) {
													if ( Gx <= 0.12) {
														return 0;
													}
													else {
														if ( AyXGx <= -0.24) {
															return 2;
														}
														else {
															if ( Gz_squared <= -0.14) {
																if ( Gz <= -0.07) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Ay <= -0.71) {
													if ( Gy_squared <= -0.14) {
														if ( GxXGy <= -0.01) {
															if ( AxXGy <= -0.02) {
																return 0;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gy_squared <= -0.15) {
																if ( AyXGx <= -0.17) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= 0.06) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AyXAz <= 0.31) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( GxXGz <= 0.02) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if ( Ay_squared <= -0.03) {
										if ( GyXGz <= -0.02) {
											return 2;
										}
										else {
											return 1;
										}
									}
									else {
										if ( Ay <= -0.81) {
											return 2;
										}
										else {
											if ( AzXGz <= 0.01) {
												if ( AyXGx <= -0.45) {
													if ( GxXGy <= 0.12) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gx <= 0.72) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AzXGx <= -0.1) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( Az <= 0.3) {
									if ( AyXGy <= 0.06) {
										if ( Gx <= -0.55) {
											if ( GxXGz <= -0.01) {
												if ( Ay <= -0.73) {
													return 2;
												}
												else {
													return 1;
												}
											}
											else {
												if ( Ay_squared <= 0.16) {
													if ( AyXGy <= -0.18) {
														return 1;
													}
													else {
														if ( AyXGx <= 0.43) {
															if ( GxXGy <= -0.0) {
																if ( AyXGy <= -0.09) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXGz <= -0.03) {
																return 1;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Ay <= -0.78) {
												if ( GyXGz <= -0.02) {
													if ( AyXAz <= 0.3) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXAz <= 0.44) {
														if ( AxXGz <= -0.03) {
															return 2;
														}
														else {
															if ( Gy_squared <= -0.16) {
																if ( Gz <= -0.09) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AxXAy <= 0.08) {
													if ( AzXGx <= 0.01) {
														if ( Gy <= 0.18) {
															if ( AzXGy <= -0.0) {
																if ( AzXGz <= 0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( Gx_squared <= -0.14) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AxXGy <= 0.02) {
															if ( GxXGy <= 0.01) {
																if ( Az_squared <= -0.11) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gz <= 0.14) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GyXGz <= -0.01) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( Az_squared <= -0.16) {
														if ( AyXGz <= -0.02) {
															if ( Gy <= 0.03) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.22) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GyXGz <= -0.03) {
																if ( AxXAy <= 0.28) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= -0.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( Gy <= 0.15) {
															if ( AzXGz <= 0.02) {
																if ( Az <= -0.09) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GxXGy <= -0.01) {
																return 0;
															}
															else {
																if ( Gz <= 0.1) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Gz <= 0.06) {
											if ( AyXGz <= 0.21) {
												if ( AxXGx <= -0.02) {
													if ( GxXGz <= 0.01) {
														if ( AyXGz <= -0.03) {
															return 0;
														}
														else {
															if ( GyXGz <= -0.03) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXAz <= 0.22) {
															return 1;
														}
														else {
															if ( AyXGx <= 0.27) {
																if ( AzXGx <= 0.08) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( GxXGz <= 0.01) {
														if ( Az_squared <= -0.17) {
															if ( AzXGx <= 0.03) {
																if ( AzXGy <= 0.01) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Ay_squared <= 0.16) {
																if ( AxXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AzXGy <= 0.05) {
															if ( Gx <= -0.4) {
																return 0;
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( Ay_squared <= 0.18) {
													if ( AyXGy <= 0.13) {
														return 0;
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( Az <= 0.01) {
												if ( AxXAy <= 0.39) {
													if ( Ay_squared <= 0.06) {
														if ( Gz_squared <= -0.13) {
															if ( GxXGz <= 0.0) {
																return 1;
															}
															else {
																if ( GxXGy <= 0.0) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( AyXGz <= -0.11) {
															return 2;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Gx_squared <= -0.13) {
													if ( Ay <= -0.68) {
														if ( GyXGz <= -0.05) {
															return 2;
														}
														else {
															if ( AxXAz <= 0.13) {
																if ( GxXGy <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.02) {
										if ( Gz_squared <= -0.14) {
											if ( AyXGz <= 0.07) {
												if ( AyXGy <= 0.06) {
													if ( AzXGx <= 0.01) {
														return 0;
													}
													else {
														if ( Ax <= -0.29) {
															if ( GyXGz <= -0.02) {
																return 0;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AyXGy <= -0.13) {
												if ( Gz <= 0.17) {
													if ( GyXGz <= -0.01) {
														return 0;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Gx <= 0.26) {
													if ( Ax <= -0.51) {
														if ( AxXAz <= 0.09) {
															if ( AxXGx <= -0.01) {
																if ( Gx <= 0.01) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGz <= -0.01) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Az_squared <= -0.23) {
																return 0;
															}
															else {
																if ( AyXGx <= -0.1) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AxXGy <= 0.0) {
															if ( Ay <= -0.73) {
																if ( AxXGy <= -0.0) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( GxXGy <= 0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Gz <= 0.18) {
																if ( GxXGz <= 0.0) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if ( Gx <= 0.23) {
											if ( Gy_squared <= -0.14) {
												if ( AxXGy <= -0.0) {
													if ( Gz_squared <= -0.14) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Ay <= -0.78) {
														return 2;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AxXAy <= 0.19) {
													return 2;
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 1;
										}
									}
								}
							}
						}
						else {
							if ( Ay_squared <= 0.31) {
								if ( Gy_squared <= -0.01) {
									if ( GxXGy <= -0.08) {
										if ( Gx_squared <= -0.09) {
											return 2;
										}
										else {
											if ( GxXGy <= -0.12) {
												return 2;
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Gx <= -0.37) {
											if ( Gz <= 0.07) {
												if ( AzXGy <= -0.13) {
													return 1;
												}
												else {
													if ( Gx <= -0.46) {
														if ( AxXGz <= -0.01) {
															return 0;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( GxXGy <= 0.06) {
												if ( AyXAz <= 0.14) {
													if ( AxXGy <= 0.05) {
														return 2;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gy_squared <= -0.08) {
														if ( AyXAz <= 0.16) {
															return 2;
														}
														else {
															if ( AzXGy <= -0.13) {
																return 0;
															}
															else {
																if ( GxXGy <= -0.05) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Ay <= -0.69) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Ay_squared <= -0.12) {
													return 2;
												}
												else {
													if ( Ay <= -0.73) {
														if ( Gy <= 0.79) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if ( AxXGy <= -0.13) {
										return 2;
									}
									else {
										if ( GxXGz <= -0.02) {
											return 2;
										}
										else {
											if ( Ay_squared <= -0.12) {
												return 2;
											}
											else {
												if ( GxXGy <= 0.14) {
													if ( AzXGz <= 0.01) {
														if ( AxXGx <= -0.01) {
															return 2;
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGy <= 0.18) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
							}
							else {
								if ( Gx <= -1.38) {
									return 0;
								}
								else {
									if ( AyXGy <= -0.69) {
										return 2;
									}
									else {
										return 2;
									}
								}
							}
						}
					}
				}
			}
			else {
				if ( AyXAz <= -0.54) {
					if ( Gx_squared <= -0.12) {
						if ( AxXAz <= 0.05) {
							if ( Gy_squared <= -0.09) {
								if ( Ax <= 2.2) {
									if ( Az_squared <= 0.81) {
										if ( Az_squared <= 0.0) {
											if ( AxXGy <= 0.0) {
												if ( AzXGx <= 0.01) {
													if ( AxXGz <= -0.03) {
														return 1;
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( Ay_squared <= 0.01) {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXAz <= 0.01) {
																if ( Ay <= 1.34) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( Ay <= 1.24) {
														return 2;
													}
													else {
														if ( AyXGz <= -0.12) {
															return 2;
														}
														else {
															if ( Gx <= -0.3) {
																if ( AxXAy <= 0.64) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXGy <= -0.04) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gz <= -0.03) {
													if ( AxXGy <= 0.03) {
														if ( Gz_squared <= -0.13) {
															if ( Gy <= 0.53) {
																if ( Gx_squared <= -0.15) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( GxXGy <= -0.01) {
															return 2;
														}
														else {
															if ( Gy <= 0.69) {
																if ( AxXGx <= -0.03) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( Ay_squared <= 0.16) {
														if ( Ay <= 1.29) {
															return 2;
														}
														else {
															if ( GxXGy <= -0.0) {
																return 2;
															}
															else {
																if ( AxXGz <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( GxXGy <= 0.0) {
												if ( Ay <= 1.15) {
													return 2;
												}
												else {
													if ( AzXGz <= 0.13) {
														if ( Gy_squared <= -0.14) {
															if ( AzXGy <= 0.09) {
																if ( Gx <= -0.32) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXGz <= -0.02) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AxXAy <= 0.27) {
													if ( AyXGy <= -0.11) {
														return 1;
													}
													else {
														if ( AyXAz <= -0.8) {
															if ( Gz_squared <= -0.14) {
																return 2;
															}
															else {
																if ( Az_squared <= 0.04) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Ay <= 1.36) {
																return 2;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( Az_squared <= 0.75) {
														if ( AzXGy <= -0.01) {
															if ( GxXGz <= -0.0) {
																return 2;
															}
															else {
																if ( Az_squared <= 0.24) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( Ay <= 1.49) {
																if ( GxXGz <= 0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										if ( AzXGz <= -0.02) {
											if ( AxXGy <= 0.09) {
												if ( GxXGy <= 0.01) {
													return 1;
												}
												else {
													if ( AyXAz <= -1.23) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( Ay_squared <= -0.59) {
										if ( Ay_squared <= -0.79) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
							}
							else {
								if ( AzXGy <= -0.22) {
									if ( AxXGx <= 0.01) {
										if ( Gy <= 0.86) {
											return 2;
										}
										else {
											if ( Gz_squared <= -0.14) {
												return 2;
											}
											else {
												if ( Gz_squared <= -0.14) {
													return 2;
												}
												else {
													if ( AxXGy <= 0.22) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( Gy_squared <= -0.0) {
											return 2;
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( Gz <= 0.16) {
										if ( Gy_squared <= -0.0) {
											if ( AxXGz <= -0.01) {
												if ( AyXGy <= -0.43) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												if ( GxXGy <= 0.07) {
													return 2;
												}
												else {
													return 1;
												}
											}
										}
										else {
											if ( Gz_squared <= -0.14) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
									else {
										return 2;
									}
								}
							}
						}
						else {
							if ( AyXGz <= 0.05) {
								if ( Gy_squared <= -0.16) {
									if ( AyXGx <= -0.03) {
										if ( AyXAz <= -0.64) {
											if ( Az_squared <= 0.01) {
												if ( GxXGz <= 0.02) {
													if ( AzXGy <= 0.01) {
														if ( Ay_squared <= -0.08) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( AzXGz <= 0.11) {
											if ( Ay_squared <= 0.06) {
												if ( AyXAz <= -0.6) {
													if ( Az <= -0.45) {
														if ( Ay <= 1.24) {
															if ( AxXAz <= 0.82) {
																if ( GxXGz <= 0.0) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXAz <= -0.8) {
																return 2;
															}
															else {
																if ( Ay_squared <= -0.08) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( Ay_squared <= -0.08) {
															if ( Gx_squared <= -0.15) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gy <= 0.09) {
																if ( GyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gz_squared <= -0.14) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Az_squared <= 0.03) {
										if ( Ay <= 1.5) {
											if ( AyXGy <= 0.38) {
												if ( Gy_squared <= -0.15) {
													if ( AyXAz <= -0.63) {
														if ( Az <= -0.49) {
															return 2;
														}
														else {
															if ( AxXGz <= -0.0) {
																if ( Gx_squared <= -0.14) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gy_squared <= -0.04) {
														if ( Ay_squared <= -0.17) {
															return 2;
														}
														else {
															if ( GyXGz <= -0.02) {
																if ( AxXGy <= -0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXGx <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gy_squared <= -0.07) {
											if ( AzXGy <= -0.16) {
												return 2;
											}
											else {
												if ( Az_squared <= 0.09) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( AzXGy <= 0.18) {
									if ( AyXGy <= 0.33) {
										if ( Gy <= -0.14) {
											if ( AyXAz <= -1.21) {
												return 1;
											}
											else {
												if ( Az <= -0.27) {
													if ( Gy <= -0.27) {
														if ( Az <= -0.49) {
															return 2;
														}
														else {
															return 0;
														}
													}
													else {
														if ( AxXAz <= 0.16) {
															if ( AxXAy <= 0.05) {
																return 1;
															}
															else {
																if ( AyXGy <= -0.19) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( GyXGz <= -0.03) {
														if ( Gy_squared <= -0.14) {
															return 1;
														}
														else {
															if ( AxXGz <= -0.02) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( AyXGz <= 0.11) {
												if ( AyXAz <= -0.75) {
													if ( AyXGz <= 0.1) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( Az <= -0.13) {
														if ( AxXGx <= -0.0) {
															if ( GxXGy <= 0.01) {
																if ( GxXGz <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( Az <= -0.35) {
													if ( Az <= -0.45) {
														if ( AxXGx <= -0.01) {
															if ( Az_squared <= 0.81) {
																if ( Az_squared <= 0.71) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( Gz_squared <= -0.14) {
															return 0;
														}
														else {
															if ( Gx_squared <= -0.14) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( GxXGy <= 0.02) {
														if ( GxXGz <= 0.01) {
															if ( AzXGx <= 0.02) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( GyXGz <= -0.01) {
																if ( Ay <= 1.4) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									if ( GyXGz <= -0.03) {
										if ( Az_squared <= -0.01) {
											return 2;
										}
										else {
											return 2;
										}
									}
									else {
										return 1;
									}
								}
							}
						}
					}
					else {
						if ( Az_squared <= 0.0) {
							if ( Gy_squared <= 0.01) {
								if ( Ay <= 1.24) {
									return 2;
								}
								else {
									if ( Ay_squared <= 0.45) {
										if ( Gx_squared <= -0.08) {
											if ( AyXGy <= 0.27) {
												if ( Az_squared <= -0.08) {
													if ( GxXGy <= 0.11) {
														if ( AyXGx <= -0.26) {
															if ( Gz_squared <= -0.14) {
																return 1;
															}
															else {
																return 2;
															}
														}
														else {
															if ( Gy_squared <= -0.13) {
																if ( Gy_squared <= -0.16) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Ay <= 1.42) {
														if ( AxXAy <= 0.11) {
															if ( Gx_squared <= -0.1) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															if ( GxXGy <= -0.02) {
																return 2;
															}
															else {
																if ( AxXAz <= -0.17) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AzXGx <= -0.15) {
															return 1;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( GxXGz <= 0.0) {
													return 2;
												}
												else {
													if ( AxXGz <= -0.02) {
														return 2;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Az_squared <= -0.1) {
												if ( Gz <= -0.25) {
													return 2;
												}
												else {
													if ( AzXGx <= 0.22) {
														if ( AxXGx <= 0.28) {
															if ( AyXAz <= -0.58) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( GxXGy <= -0.08) {
													return 2;
												}
												else {
													if ( AyXGy <= -0.46) {
														return 0;
													}
													else {
														if ( AzXGx <= -0.16) {
															if ( Gx <= 1.03) {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gx <= 1.2) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AyXGz <= -0.02) {
																return 2;
															}
															else {
																if ( GxXGz <= 0.02) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( Gx_squared <= 0.13) {
									if ( AxXGz <= 0.0) {
										if ( AzXGy <= -0.38) {
											return 2;
										}
										else {
											if ( Az_squared <= -0.08) {
												return 2;
											}
											else {
												if ( AxXGz <= -0.01) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									if ( Az <= -0.09) {
										if ( AxXAz <= 0.11) {
											if ( Ay_squared <= -0.1) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if ( AxXAy <= 0.35) {
								if ( Gx_squared <= -0.1) {
									if ( Az_squared <= 0.04) {
										return 2;
									}
									else {
										if ( Gy_squared <= -0.08) {
											if ( AxXAy <= 0.28) {
												if ( AxXGy <= 0.02) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 1;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AzXGx <= 1.33) {
										if ( AzXGy <= -0.11) {
											if ( Gx_squared <= 0.67) {
												if ( Az <= -0.74) {
													if ( Az <= -1.49) {
														return 2;
													}
													else {
														if ( Ax <= -0.29) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AxXAy <= 0.08) {
														return 2;
													}
													else {
														if ( Gx_squared <= -0.06) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Gy <= -0.92) {
												if ( AyXGx <= -0.86) {
													return 2;
												}
												else {
													if ( Gz_squared <= -0.14) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Az <= -0.56) {
													if ( AyXGy <= -0.47) {
														return 2;
													}
													else {
														if ( AzXGx <= -0.34) {
															return 2;
														}
														else {
															if ( AyXAz <= -0.8) {
																if ( Ay_squared <= 0.39) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( GxXGy <= -0.01) {
									if ( GxXGz <= -0.08) {
										return 2;
									}
									else {
										if ( AxXAz <= -0.08) {
											if ( AyXGx <= -0.26) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( Gy_squared <= -0.02) {
										if ( Ay_squared <= 0.21) {
											if ( Ay_squared <= -0.27) {
												if ( Az <= -1.39) {
													return 1;
												}
												else {
													return 2;
												}
											}
											else {
												if ( Gz_squared <= -0.14) {
													if ( AyXGx <= 0.27) {
														if ( Ax_squared <= 0.02) {
															if ( AxXGx <= -0.09) {
																return 2;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( Gx_squared <= -0.08) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AzXGx <= 0.48) {
											if ( AyXGz <= -0.08) {
												return 2;
											}
											else {
												if ( Gy_squared <= 0.02) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( Az <= -0.63) {
						if ( AyXGy <= -0.33) {
							if ( AxXGz <= 0.01) {
								if ( GxXGz <= 0.0) {
									if ( AzXGy <= -0.61) {
										if ( GxXGy <= 0.13) {
											if ( Gz_squared <= -0.13) {
												if ( Gz_squared <= -0.14) {
													return 1;
												}
												else {
													if ( AxXAy <= 0.04) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 1;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AxXAy <= 0.18) {
											if ( AyXGx <= -0.14) {
												if ( AyXAz <= 0.66) {
													return 1;
												}
												else {
													if ( AxXGx <= 0.06) {
														if ( AyXAz <= 0.82) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( AzXGx <= -0.21) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Az <= -1.53) {
													return 1;
												}
												else {
													if ( AzXGy <= -0.53) {
														if ( Ax <= 1.22) {
															if ( AxXGy <= 0.01) {
																return 1;
															}
															else {
																if ( AxXGx <= 0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( AyXGy <= -0.53) {
															return 1;
														}
														else {
															if ( Az_squared <= 0.37) {
																if ( AzXGz <= 0.11) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											if ( AxXGz <= -0.03) {
												return 1;
											}
											else {
												if ( AxXAy <= 0.26) {
													if ( AxXAy <= 0.22) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
										}
									}
								}
								else {
									if ( GxXGz <= 0.02) {
										if ( AxXGy <= -0.14) {
											return 0;
										}
										else {
											if ( AyXAz <= 0.58) {
												return 2;
											}
											else {
												if ( Gy <= 1.26) {
													if ( Gx_squared <= -0.14) {
														if ( GyXGz <= -0.01) {
															if ( Gy <= 0.76) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( AxXGy <= -0.11) {
									if ( AxXGx <= -0.04) {
										if ( GxXGz <= -0.0) {
											return 0;
										}
										else {
											return 0;
										}
									}
									else {
										return 0;
									}
								}
								else {
									if ( GyXGz <= 0.02) {
										if ( GxXGz <= 0.0) {
											if ( AzXGy <= -0.41) {
												if ( Gy_squared <= -0.01) {
													if ( AzXGy <= -0.54) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AzXGy <= -0.29) {
													if ( AxXGz <= 0.03) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 2;
									}
								}
							}
						}
						else {
							if ( GyXGz <= -0.02) {
								if ( Gy <= -1.22) {
									if ( GxXGy <= -0.29) {
										if ( AxXGy <= 0.2) {
											if ( Az_squared <= 0.12) {
												return 0;
											}
											else {
												if ( Ay <= -0.52) {
													if ( Gx <= 1.09) {
														if ( Gx_squared <= -0.02) {
															return 1;
														}
														else {
															if ( Gz_squared <= -0.13) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXAz <= 0.08) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gx <= 0.76) {
											if ( AyXGy <= 0.65) {
												return 0;
											}
											else {
												if ( AxXAy <= 0.39) {
													if ( Gx <= 0.57) {
														return 2;
													}
													else {
														if ( Az_squared <= 0.14) {
															return 0;
														}
														else {
															if ( AzXGx <= -0.31) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXAz <= -0.29) {
												if ( AzXGy <= 0.84) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												if ( Az <= -1.24) {
													if ( Ay <= -0.41) {
														if ( Ax_squared <= -0.11) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXAy <= 0.38) {
														if ( AzXGz <= -0.06) {
															return 0;
														}
														else {
															if ( GyXGz <= -0.04) {
																if ( GxXGy <= -0.25) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.01) {
										if ( AzXGz <= -0.03) {
											if ( Az <= -2.03) {
												return 0;
											}
											else {
												if ( Az <= -0.85) {
													if ( AyXAz <= 0.54) {
														return 0;
													}
													else {
														if ( AzXGy <= 0.65) {
															if ( AyXAz <= 0.84) {
																if ( AxXAz <= -0.54) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AyXGy <= 0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AyXGy <= 0.06) {
														if ( AyXGy <= 0.01) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														if ( Gy <= -0.88) {
															return 0;
														}
														else {
															if ( GxXGz <= 0.02) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
										else {
											if ( AxXGx <= -0.07) {
												if ( AyXGz <= 0.06) {
													if ( Gy_squared <= -0.1) {
														if ( Ay <= -0.59) {
															return 0;
														}
														else {
															if ( Gx <= -0.45) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXGz <= -0.04) {
														if ( GyXGz <= -0.04) {
															return 1;
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AyXGy <= -0.13) {
													if ( Gy <= 0.42) {
														if ( AxXAz <= -0.1) {
															if ( Ay_squared <= -0.33) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGx <= 0.13) {
																if ( AxXAz <= 0.17) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AzXGx <= 0.09) {
															if ( GxXGz <= 0.01) {
																if ( AzXGy <= -0.25) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AxXAz <= -0.09) {
																return 0;
															}
															else {
																if ( Gx <= -0.52) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AxXAy <= 0.52) {
														if ( AzXGx <= -0.07) {
															if ( GxXGy <= -0.04) {
																if ( AzXGy <= 0.45) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ax_squared <= -0.12) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Ax <= 2.31) {
																if ( AyXGy <= 0.11) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( AyXGx <= 0.12) {
											if ( Ax <= -0.19) {
												if ( Az <= -1.17) {
													if ( Ax_squared <= -0.03) {
														if ( AzXGy <= -0.23) {
															if ( AyXGy <= -0.23) {
																return 1;
															}
															else {
																if ( AzXGz <= 0.08) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AzXGz <= -0.03) {
																if ( Ay_squared <= -0.62) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXAy <= 0.75) {
														if ( Gy <= 0.38) {
															if ( AyXAz <= 0.63) {
																return 1;
															}
															else {
																if ( AxXGx <= -0.01) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GyXGz <= -0.05) {
																return 1;
															}
															else {
																if ( GyXGz <= -0.04) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AxXAy <= -0.78) {
													if ( Gz <= 0.07) {
														if ( GxXGz <= 0.01) {
															if ( Ay <= -0.51) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AzXGy <= 0.15) {
														if ( AzXGz <= -0.12) {
															if ( Gz <= 0.14) {
																return 0;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Az_squared <= 0.3) {
																if ( Gx <= 0.02) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGy <= 0.06) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( Ay_squared <= -0.31) {
															return 0;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
										else {
											if ( AyXAz <= 0.64) {
												return 2;
											}
											else {
												if ( AzXGx <= 0.16) {
													return 1;
												}
												else {
													if ( GxXGy <= 0.07) {
														if ( AxXGz <= -0.01) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( AyXGy <= 0.21) {
									if ( AxXGx <= 0.08) {
										if ( AxXAy <= -0.51) {
											if ( AyXGx <= -0.01) {
												return 0;
											}
											else {
												if ( AzXGy <= -0.4) {
													return 0;
												}
												else {
													if ( AyXGz <= -0.06) {
														return 1;
													}
													else {
														if ( Ay_squared <= -0.31) {
															return 2;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
										else {
											if ( AxXGx <= -0.04) {
												if ( Gz <= -0.28) {
													if ( Ay <= -0.55) {
														return 2;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gy <= 0.21) {
														if ( Az_squared <= 0.26) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														if ( AzXGx <= 0.14) {
															if ( AzXGz <= -0.07) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXAy <= -0.37) {
																return 0;
															}
															else {
																if ( AzXGz <= -0.16) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AzXGy <= -0.36) {
													return 0;
												}
												else {
													if ( GxXGy <= 0.02) {
														if ( AyXAz <= 0.58) {
															return 2;
														}
														else {
															if ( AxXAy <= 0.48) {
																if ( AxXAz <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGx <= 0.11) {
															if ( Ay <= -0.37) {
																if ( AzXGy <= 0.21) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
									else {
										if ( AzXGy <= 0.06) {
											if ( AyXGz <= -0.03) {
												return 0;
											}
											else {
												if ( AyXGx <= -0.18) {
													return 1;
												}
												else {
													if ( AxXAz <= -0.66) {
														return 0;
													}
													else {
														if ( AxXAy <= -0.47) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
											}
										}
										else {
											if ( Ay <= -0.53) {
												if ( AyXAz <= 0.7) {
													if ( GxXGy <= -0.01) {
														if ( AyXGz <= 0.2) {
															if ( GxXGz <= -0.01) {
																if ( AyXGz <= 0.17) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ax <= 1.38) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( GxXGz <= -0.02) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AyXGy <= 0.12) {
													if ( Gz_squared <= -0.14) {
														return 1;
													}
													else {
														if ( AxXGz <= -0.15) {
															return 1;
														}
														else {
															if ( AxXAy <= -0.25) {
																if ( Ay_squared <= -0.55) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AxXAy <= -0.5) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if ( AzXGx <= -0.24) {
										if ( AzXGx <= -0.46) {
											if ( GxXGy <= -0.77) {
												return 2;
											}
											else {
												if ( Gx_squared <= -0.02) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Ay <= -0.51) {
												if ( Ay_squared <= -0.19) {
													if ( Ax_squared <= -0.11) {
														return 1;
													}
													else {
														if ( Gz <= -0.19) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( AyXGy <= 0.31) {
											if ( AyXGx <= 0.17) {
												if ( Gx_squared <= -0.14) {
													return 2;
												}
												else {
													if ( AyXAz <= 0.82) {
														if ( AzXGz <= 0.05) {
															return 2;
														}
														else {
															if ( Gy_squared <= -0.13) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AyXAz <= 0.66) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( Ay <= 1.27) {
							if ( AxXAz <= -0.21) {
								if ( AxXAy <= -1.3) {
									if ( Gz <= 0.02) {
										return 1;
									}
									else {
										if ( Ay_squared <= -0.68) {
											return 1;
										}
										else {
											if ( Gx_squared <= -0.14) {
												if ( Ax_squared <= 1.44) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AyXGy <= 0.18) {
										if ( Gx_squared <= -0.11) {
											if ( AyXGx <= -0.1) {
												if ( Ax_squared <= 0.68) {
													if ( GxXGy <= -0.01) {
														if ( AzXGy <= 0.08) {
															if ( AyXGx <= -0.18) {
																return 1;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( AxXGz <= 0.08) {
															if ( AzXGy <= -0.31) {
																return 1;
															}
															else {
																if ( Gy_squared <= -0.16) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Ax <= 3.82) {
													if ( AyXGx <= -0.02) {
														if ( AxXAz <= -0.62) {
															return 0;
														}
														else {
															if ( AzXGz <= 0.12) {
																if ( AyXGz <= 0.14) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AxXAz <= -0.63) {
															return 2;
														}
														else {
															if ( Ax <= 3.28) {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
												else {
													if ( AzXGy <= 0.01) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( AyXGy <= 0.05) {
												if ( GyXGz <= 0.01) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Gy <= -0.98) {
											if ( GxXGz <= -0.03) {
												return 2;
											}
											else {
												if ( AzXGy <= 0.47) {
													if ( AxXAz <= -0.24) {
														if ( Ax <= 1.98) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AyXGy <= 0.31) {
												if ( Gz <= 0.02) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( Ay_squared <= -0.29) {
									if ( Ax_squared <= 0.65) {
										if ( Ay <= 1.21) {
											if ( AxXAy <= 0.25) {
												if ( Ay <= 1.17) {
													if ( AyXAz <= 0.5) {
														if ( AxXGx <= -0.34) {
															return 2;
														}
														else {
															if ( Ay <= -0.5) {
																if ( GxXGz <= 0.01) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAz <= 0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( AxXAz <= 0.21) {
													if ( AyXAz <= -0.24) {
														if ( AzXGy <= -0.1) {
															return 2;
														}
														else {
															if ( Gz_squared <= -0.14) {
																return 2;
															}
															else {
																if ( AzXGx <= 0.13) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AyXAz <= 0.14) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AxXAz <= -0.0) {
												return 2;
											}
											else {
												if ( AyXAz <= -0.45) {
													return 2;
												}
												else {
													if ( Gx <= 0.27) {
														return 1;
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( AyXGz <= -0.01) {
											return 0;
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Gy_squared <= -0.14) {
										if ( Gx <= 0.03) {
											if ( Gx <= -0.37) {
												if ( AyXAz <= -0.21) {
													return 1;
												}
												else {
													if ( AxXAz <= 0.0) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AzXGz <= 0.04) {
													if ( GxXGz <= 0.0) {
														return 1;
													}
													else {
														if ( Gz_squared <= -0.14) {
															return 2;
														}
														else {
															if ( AyXGz <= 0.08) {
																if ( Gz <= -0.04) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AyXAz <= 0.5) {
														return 2;
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( AzXGz <= 0.1) {
												if ( Ax <= 1.66) {
													if ( Gz <= -0.34) {
														return 2;
													}
													else {
														if ( AxXAz <= -0.17) {
															return 1;
														}
														else {
															if ( AzXGx <= 0.01) {
																if ( GxXGy <= 0.04) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AxXAy <= -1.09) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( AyXAz <= 0.48) {
											if ( Ay <= 0.34) {
												if ( AxXAy <= -1.11) {
													return 1;
												}
												else {
													if ( AxXAz <= -0.14) {
														if ( Ay_squared <= -0.25) {
															return 2;
														}
														else {
															if ( AzXGx <= -0.0) {
																return 1;
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGx <= -0.47) {
															return 2;
														}
														else {
															if ( AyXGy <= 0.83) {
																if ( AxXAz <= 0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
											}
											else {
												if ( AzXGy <= 0.06) {
													return 1;
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AxXAy <= -0.09) {
												if ( AyXAz <= 0.54) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												if ( AyXGx <= 0.22) {
													if ( AyXGz <= -0.02) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXGy <= 0.31) {
								if ( Gy <= -0.69) {
									if ( Gz <= 0.18) {
										if ( Gy <= -1.12) {
											if ( Ay_squared <= -0.08) {
												return 2;
											}
											else {
												if ( GyXGz <= -0.06) {
													return 0;
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( GyXGz <= -0.01) {
												if ( GxXGy <= 0.13) {
													if ( GyXGz <= -0.07) {
														return 0;
													}
													else {
														if ( AxXAy <= 0.68) {
															return 1;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( AxXGx <= -0.0) {
											return 2;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( GxXGy <= 0.01) {
										if ( Gx_squared <= -0.12) {
											if ( GyXGz <= -0.03) {
												if ( AyXGz <= 0.16) {
													if ( AxXGy <= -0.02) {
														return 0;
													}
													else {
														if ( AyXGx <= 0.07) {
															if ( Gy_squared <= -0.14) {
																if ( AyXGy <= -0.18) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AxXGz <= -0.07) {
														return 0;
													}
													else {
														if ( AxXGy <= -0.08) {
															return 2;
														}
														else {
															if ( AzXGx <= 0.0) {
																if ( AxXAz <= 0.12) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ay <= 1.4) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( AxXAy <= 0.44) {
													if ( AyXGx <= -0.06) {
														if ( Gz_squared <= -0.14) {
															if ( Gz <= -0.07) {
																if ( AzXGx <= 0.06) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gx <= -0.29) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXAz <= -0.22) {
																if ( AzXGx <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AzXGx <= -0.03) {
															if ( AyXAz <= -0.46) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( Ay_squared <= 0.11) {
																if ( GyXGz <= -0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGz <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AxXGy <= 0.02) {
														if ( Gy_squared <= -0.12) {
															if ( AxXGy <= -0.05) {
																return 0;
															}
															else {
																if ( Az <= 0.05) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AzXGy <= -0.06) {
															return 1;
														}
														else {
															if ( AzXGz <= 0.01) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											if ( Ax_squared <= -0.02) {
												if ( AyXAz <= -0.44) {
													if ( AxXGx <= -0.11) {
														return 2;
													}
													else {
														if ( AyXGx <= 0.41) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( GxXGy <= -0.08) {
														return 2;
													}
													else {
														if ( Gy <= -0.06) {
															return 1;
														}
														else {
															if ( Gy_squared <= -0.16) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( Ax <= 0.09) {
											if ( GyXGz <= -0.02) {
												if ( AyXGx <= -0.01) {
													if ( AzXGx <= 0.08) {
														if ( AyXGz <= 0.08) {
															if ( Az <= 0.59) {
																if ( Gy <= -0.31) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGy <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GyXGz <= -0.03) {
																if ( Ay <= 1.4) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Ay <= 1.37) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AzXGy <= 0.1) {
															if ( Gy <= -0.32) {
																return 1;
															}
															else {
																if ( AxXAz <= 0.05) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Gy <= 0.13) {
														if ( GyXGz <= -0.03) {
															if ( AzXGz <= -0.01) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AxXAy <= 0.22) {
																if ( Ay <= 1.41) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Az_squared <= -0.19) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( Ay_squared <= 0.26) {
															if ( AxXAz <= -0.0) {
																return 2;
															}
															else {
																if ( GxXGz <= 0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Gx <= -0.54) {
													return 2;
												}
												else {
													if ( Az_squared <= -0.16) {
														if ( Gy <= 0.33) {
															if ( Gz <= 0.08) {
																if ( AxXGx <= 0.02) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGx <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AyXGy <= 0.22) {
																if ( AzXGx <= -0.07) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														if ( AyXGy <= 0.16) {
															if ( AyXGy <= -0.0) {
																if ( Gy_squared <= -0.12) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGx <= 0.13) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gx <= 0.49) {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											if ( AxXGy <= -0.03) {
												if ( Gx_squared <= -0.08) {
													if ( GxXGz <= 0.01) {
														if ( Gx <= -0.39) {
															if ( AxXGz <= 0.07) {
																if ( AzXGx <= 0.1) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Az <= 0.44) {
																if ( AzXGz <= -0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( GyXGz <= -0.01) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Gx <= 0.32) {
													if ( Gz_squared <= -0.14) {
														if ( AyXGx <= -0.04) {
															return 1;
														}
														else {
															if ( GyXGz <= -0.02) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( GxXGz <= 0.01) {
															if ( AxXGx <= -0.0) {
																if ( AyXGz <= 0.23) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXAz <= -0.05) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( Gz_squared <= -0.14) {
																if ( AxXGx <= -0.09) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AxXGx <= 0.03) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AzXGz <= -0.02) {
														return 0;
													}
													else {
														if ( Gz <= 0.01) {
															if ( Gz_squared <= -0.14) {
																return 1;
															}
															else {
																if ( Az_squared <= -0.22) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Gy_squared <= -0.05) {
									if ( AzXGz <= 0.01) {
										if ( GxXGy <= -0.01) {
											return 2;
										}
										else {
											if ( AxXGz <= 0.04) {
												if ( AxXGy <= 0.1) {
													if ( AzXGy <= -0.07) {
														if ( AyXGz <= 0.11) {
															return 1;
														}
														else {
															if ( AxXAy <= -0.05) {
																return 1;
															}
															else {
																if ( AxXAy <= 0.2) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Gz_squared <= -0.14) {
											if ( AzXGy <= -0.06) {
												if ( Gx_squared <= -0.08) {
													if ( AxXGx <= 0.07) {
														if ( Ay <= 1.4) {
															return 1;
														}
														else {
															return 1;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Ay <= 1.41) {
												if ( Ay <= 1.38) {
													return 1;
												}
												else {
													if ( AzXGz <= 0.01) {
														return 1;
													}
													else {
														if ( AxXGx <= 0.06) {
															if ( AyXGy <= 0.39) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
											else {
												if ( Gx <= 0.02) {
													return 2;
												}
												else {
													if ( AyXGy <= 0.39) {
														return 1;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.06) {
										if ( GxXGy <= -0.13) {
											return 1;
										}
										else {
											if ( AyXGz <= 0.01) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( Gy <= 1.13) {
											if ( AzXGz <= 0.05) {
												if ( AzXGy <= -0.1) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Gx_squared <= -0.09) {
												return 2;
											}
											else {
												if ( AzXGx <= -0.14) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			if ( Ay <= 1.21) {
				if ( Gz <= -0.24) {
					if ( Gy_squared <= -0.15) {
						if ( AyXGx <= 0.01) {
							if ( AzXGy <= -0.02) {
								if ( AxXGy <= -0.1) {
									return 1;
								}
								else {
									if ( AxXGx <= -0.0) {
										if ( AzXGx <= 0.01) {
											return 0;
										}
										else {
											if ( AyXGz <= 0.19) {
												if ( GyXGz <= -0.02) {
													if ( GxXGz <= 0.0) {
														if ( AzXGy <= -0.03) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										if ( Ay_squared <= 0.13) {
											if ( AxXAy <= -0.89) {
												return 0;
											}
											else {
												if ( AyXGx <= -0.25) {
													return 2;
												}
												else {
													if ( AzXGz <= -0.0) {
														if ( Gx_squared <= -0.14) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.15) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( AxXAy <= -0.7) {
									return 2;
								}
								else {
									if ( Gz <= -0.44) {
										return 0;
									}
									else {
										if ( Ax_squared <= -0.07) {
											if ( Gy_squared <= -0.16) {
												return 2;
											}
											else {
												if ( Gx_squared <= -0.15) {
													return 2;
												}
												else {
													if ( GxXGy <= 0.01) {
														return 0;
													}
													else {
														if ( AxXGz <= 0.01) {
															if ( GyXGz <= -0.03) {
																if ( Gz <= -0.38) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
										}
										else {
											if ( Gy <= 0.3) {
												if ( GxXGy <= 0.01) {
													if ( AxXAz <= 0.22) {
														if ( AxXAz <= 0.15) {
															if ( AyXGz <= 0.19) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXGy <= -0.05) {
								if ( AzXGx <= 0.01) {
									if ( AxXGz <= 0.03) {
										if ( AxXAy <= -0.81) {
											return 2;
										}
										else {
											if ( AzXGz <= -0.04) {
												if ( AyXAz <= -0.75) {
													return 0;
												}
												else {
													return 2;
												}
											}
											else {
												if ( Gx_squared <= -0.14) {
													return 0;
												}
												else {
													if ( AyXAz <= -0.28) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										return 0;
									}
								}
								else {
									return 2;
								}
							}
							else {
								if ( AyXGz <= 0.2) {
									if ( Ax_squared <= -0.05) {
										if ( AyXAz <= -0.35) {
											if ( AxXGz <= 0.01) {
												if ( Ax_squared <= -0.12) {
													if ( AzXGy <= -0.07) {
														return 2;
													}
													else {
														if ( AxXAz <= 0.05) {
															return 1;
														}
														else {
															if ( AyXAz <= -0.59) {
																return 1;
															}
															else {
																if ( AzXGx <= -0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( AzXGx <= -0.09) {
														return 1;
													}
													else {
														if ( AxXGy <= -0.01) {
															if ( Gx_squared <= -0.14) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															if ( GyXGz <= -0.02) {
																if ( Gy <= 0.07) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gz_squared <= -0.14) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
											else {
												if ( AyXAz <= -0.47) {
													if ( AzXGz <= -0.05) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( GxXGy <= 0.01) {
												if ( AxXAz <= 0.03) {
													return 1;
												}
												else {
													if ( AyXGz <= 0.16) {
														if ( GxXGy <= 0.01) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( AzXGz <= 0.01) {
											if ( AzXGy <= -0.03) {
												if ( AzXGy <= -0.09) {
													return 1;
												}
												else {
													if ( GyXGz <= -0.01) {
														if ( AzXGy <= -0.05) {
															return 1;
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
											}
											else {
												if ( AzXGx <= -0.01) {
													if ( Gz <= -0.3) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													if ( AyXAz <= -0.28) {
														if ( AyXGy <= 0.02) {
															if ( Gx <= -0.14) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGz <= 0.16) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( Gy_squared <= -0.16) {
												return 2;
											}
											else {
												if ( AxXAy <= -0.67) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( Gx <= -0.28) {
										if ( AzXGy <= -0.02) {
											if ( AyXGz <= 0.21) {
												return 2;
											}
											else {
												if ( Gx <= -0.41) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( AyXAz <= -0.53) {
											return 0;
										}
										else {
											if ( AxXAz <= 0.12) {
												if ( AzXGx <= -0.0) {
													return 2;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( Gy <= -0.81) {
							if ( AzXGx <= -0.01) {
								return 2;
							}
							else {
								if ( AyXGy <= 0.82) {
									return 2;
								}
								else {
									return 2;
								}
							}
						}
						else {
							if ( AyXAz <= -1.02) {
								return 0;
							}
							else {
								if ( Ax <= 0.09) {
									if ( GxXGy <= 0.02) {
										if ( Gz_squared <= -0.13) {
											if ( GxXGy <= 0.01) {
												if ( AxXAz <= 0.03) {
													return 0;
												}
												else {
													if ( GyXGz <= -0.04) {
														return 2;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gx <= -0.6) {
											return 0;
										}
										else {
											if ( GyXGz <= 0.01) {
												if ( AxXAz <= 0.06) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( AxXAy <= -0.72) {
										if ( Gy_squared <= -0.12) {
											if ( Ay <= -0.75) {
												return 2;
											}
											else {
												if ( Gz <= -0.43) {
													return 0;
												}
												else {
													if ( AzXGx <= 0.02) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AzXGy <= 0.13) {
											if ( GxXGy <= 0.08) {
												if ( AzXGy <= 0.02) {
													if ( AxXGz <= -0.09) {
														return 0;
													}
													else {
														if ( Gz <= -0.34) {
															return 2;
														}
														else {
															if ( GyXGz <= -0.04) {
																return 0;
															}
															else {
																if ( AzXGy <= -0.04) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( Ay_squared <= -1.14) {
						if ( AxXGz <= -0.02) {
							return 1;
						}
						else {
							if ( AxXGx <= -0.0) {
								if ( AyXGy <= -0.01) {
									if ( AxXGy <= -0.0) {
										return 2;
									}
									else {
										return 2;
									}
								}
								else {
									return 2;
								}
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( Gx_squared <= -0.09) {
							if ( Az_squared <= -0.07) {
								if ( Ax_squared <= 0.08) {
									if ( AzXGy <= 0.01) {
										if ( Ax <= -1.05) {
											if ( AyXAz <= -0.31) {
												if ( Gx_squared <= -0.15) {
													if ( Gz_squared <= -0.14) {
														if ( AyXGy <= 0.04) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGx <= 0.01) {
															return 2;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( Ax <= -1.27) {
														if ( AxXAz <= -0.14) {
															return 2;
														}
														else {
															if ( GxXGy <= 0.01) {
																if ( AxXGx <= -0.08) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( GxXGz <= 0.01) {
															return 2;
														}
														else {
															if ( Gy_squared <= -0.16) {
																return 2;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gz_squared <= -0.14) {
													if ( AxXAy <= 0.53) {
														return 2;
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGz <= 0.02) {
														return 0;
													}
													else {
														if ( AxXGy <= 0.09) {
															if ( GxXGy <= 0.01) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( AxXGy <= -0.14) {
												if ( Gx_squared <= -0.11) {
													if ( Gx_squared <= -0.14) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Az_squared <= -0.16) {
													if ( Gz_squared <= -0.14) {
														if ( Az_squared <= -0.2) {
															if ( Gy_squared <= -0.16) {
																if ( Gx_squared <= -0.15) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ay <= -0.73) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AzXGz <= 0.02) {
																if ( AxXGy <= -0.04) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AxXAy <= 0.02) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( GyXGz <= -0.02) {
															if ( GyXGz <= -0.07) {
																return 2;
															}
															else {
																if ( Ay <= -0.83) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GyXGz <= 0.01) {
																if ( AxXGx <= -0.0) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AzXGz <= 0.02) {
														if ( AzXGx <= 0.03) {
															if ( AxXAy <= -0.03) {
																if ( Ay_squared <= -0.03) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXAz <= -0.57) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AxXGz <= -0.02) {
																return 0;
															}
															else {
																if ( AzXGy <= -0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AxXAz <= 0.14) {
															if ( Gx <= -0.19) {
																return 0;
															}
															else {
																if ( AzXGy <= -0.05) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AyXAz <= -0.58) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Ax <= -1.27) {
											return 0;
										}
										else {
											if ( GyXGz <= -0.02) {
												if ( Gz_squared <= -0.14) {
													return 2;
												}
												else {
													if ( GxXGz <= 0.01) {
														return 0;
													}
													else {
														if ( Ay <= -0.68) {
															if ( AyXGz <= 0.1) {
																if ( AyXAz <= -0.59) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												if ( GyXGz <= -0.0) {
													if ( Gx_squared <= -0.13) {
														if ( AxXGz <= -0.02) {
															return 0;
														}
														else {
															if ( Ay_squared <= -0.01) {
																return 2;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
								}
								else {
									if ( Gy_squared <= -0.05) {
										if ( AyXAz <= -0.32) {
											if ( AxXAz <= 0.23) {
												if ( Gy_squared <= -0.16) {
													if ( AxXAy <= 1.02) {
														if ( Gz_squared <= -0.14) {
															if ( AxXGy <= -0.0) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AzXGz <= 0.01) {
														return 2;
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( GxXGy <= 0.03) {
													if ( Ay_squared <= 0.11) {
														if ( AxXAy <= -0.93) {
															return 0;
														}
														else {
															if ( GxXGy <= 0.01) {
																if ( Ay_squared <= -0.06) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AxXAz <= -0.01) {
												return 1;
											}
											else {
												if ( AxXGy <= 0.03) {
													if ( AxXAy <= -0.9) {
														if ( Gz_squared <= -0.14) {
															if ( Ax_squared <= 0.31) {
																return 2;
															}
															else {
																if ( AzXGx <= 0.03) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AzXGz <= 0.01) {
															return 0;
														}
														else {
															if ( Gz_squared <= -0.13) {
																if ( AyXGy <= 0.18) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( Ax <= 1.28) {
														if ( Gx <= 0.07) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														if ( GyXGz <= -0.02) {
															return 0;
														}
														else {
															if ( AzXGz <= 0.03) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AxXGz <= 0.13) {
											return 2;
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( AxXAz <= -0.29) {
									return 2;
								}
								else {
									if ( AxXAy <= 0.14) {
										if ( Az <= 3.1) {
											if ( GxXGy <= 0.01) {
												if ( Ax_squared <= 1.08) {
													if ( Gx_squared <= -0.14) {
														if ( AyXGy <= 0.05) {
															if ( GyXGz <= -0.02) {
																if ( Gx <= -0.01) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGx <= -0.03) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AzXGz <= 0.06) {
																if ( AxXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( GxXGy <= 0.01) {
															if ( AxXAy <= -0.54) {
																return 2;
															}
															else {
																if ( Ay <= -0.59) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AxXAy <= -0.55) {
													return 2;
												}
												else {
													if ( AyXAz <= -0.84) {
														if ( AxXGx <= 0.06) {
															if ( AyXGx <= 0.02) {
																return 0;
															}
															else {
																if ( GyXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGy <= 0.02) {
															return 0;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AxXAy <= 0.16) {
											return 0;
										}
										else {
											if ( AzXGz <= 0.17) {
												if ( AzXGy <= -0.22) {
													return 0;
												}
												else {
													if ( Az_squared <= 0.26) {
														if ( GxXGy <= 0.01) {
															if ( AxXAz <= 0.04) {
																if ( Gx <= 0.04) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AzXGz <= -0.0) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
						else {
							if ( Gx <= 0.85) {
								if ( AyXAz <= -0.87) {
									return 0;
								}
								else {
									if ( AyXAz <= -0.29) {
										if ( Gx_squared <= -0.09) {
											return 2;
										}
										else {
											if ( GxXGy <= -0.04) {
												if ( AxXAy <= -0.57) {
													return 2;
												}
												else {
													return 0;
												}
											}
											else {
												if ( AzXGz <= 0.01) {
													return 0;
												}
												else {
													if ( Gz_squared <= -0.14) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( AyXGy <= 0.1) {
											if ( Gz_squared <= -0.14) {
												if ( AzXGy <= -0.02) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AxXGz <= 0.04) {
												return 0;
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( AyXAz <= -0.29) {
									if ( Az_squared <= -0.17) {
										return 2;
									}
									else {
										return 2;
									}
								}
								else {
									if ( Gx <= 1.84) {
										if ( Gx <= 1.36) {
											return 2;
										}
										else {
											return 2;
										}
									}
									else {
										return 0;
									}
								}
							}
						}
					}
				}
			}
			else {
				if ( Ax_squared <= -0.04) {
					if ( Gy_squared <= -0.12) {
						if ( Gy <= 0.04) {
							if ( GxXGy <= 0.01) {
								if ( GyXGz <= -0.03) {
									return 2;
								}
								else {
									if ( Gx_squared <= -0.12) {
										if ( AzXGy <= -0.03) {
											return 1;
										}
										else {
											if ( AzXGy <= -0.02) {
												return 0;
											}
											else {
												if ( GxXGz <= 0.0) {
													return 0;
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										return 1;
									}
								}
							}
							else {
								if ( Gz <= -0.2) {
									if ( AzXGy <= -0.03) {
										return 1;
									}
									else {
										return 1;
									}
								}
								else {
									if ( AxXGy <= -0.06) {
										return 0;
									}
									else {
										if ( GxXGz <= 0.0) {
											if ( Gx <= -0.35) {
												return 1;
											}
											else {
												if ( AxXGy <= -0.04) {
													return 1;
												}
												else {
													if ( Ay <= 1.37) {
														return 1;
													}
													else {
														if ( AxXAz <= 0.08) {
															if ( Ax_squared <= -0.11) {
																if ( GxXGz <= -0.0) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( AxXAy <= 0.5) {
												if ( AzXGz <= 0.02) {
													return 1;
												}
												else {
													if ( GxXGz <= 0.01) {
														if ( AzXGx <= 0.02) {
															if ( AzXGx <= 0.02) {
																if ( GxXGz <= 0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
						else {
							if ( AyXAz <= 0.34) {
								if ( AyXGx <= 0.11) {
									if ( AyXAz <= -0.06) {
										if ( AxXGz <= -0.01) {
											return 1;
										}
										else {
											return 1;
										}
									}
									else {
										if ( AxXGx <= 0.01) {
											if ( AxXAz <= 0.1) {
												if ( AxXAz <= 0.07) {
													if ( AzXGz <= 0.02) {
														return 1;
													}
													else {
														if ( AxXGz <= -0.02) {
															return 1;
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( Gx <= 0.32) {
										if ( AxXGx <= 0.04) {
											if ( Ay <= 1.41) {
												if ( Gy <= 0.44) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( GxXGy <= 0.05) {
											return 1;
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( GyXGz <= -0.02) {
							if ( AyXGy <= -0.61) {
								return 2;
							}
							else {
								if ( AyXGy <= 0.32) {
									return 1;
								}
								else {
									return 2;
								}
							}
						}
						else {
							if ( Gy_squared <= 0.05) {
								if ( AxXGz <= -0.01) {
									return 2;
								}
								else {
									return 1;
								}
							}
							else {
								return 2;
							}
						}
					}
				}
				else {
					if ( Gy_squared <= -0.1) {
						if ( AxXGz <= -0.1) {
							return 2;
						}
						else {
							if ( AzXGz <= -0.0) {
								return 0;
							}
							else {
								if ( AxXAy <= 1.09) {
									if ( AxXGz <= 0.03) {
										if ( AyXGx <= 0.0) {
											if ( Gy_squared <= -0.16) {
												return 1;
											}
											else {
												if ( Gx_squared <= -0.15) {
													return 1;
												}
												else {
													if ( GyXGz <= -0.03) {
														return 1;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AzXGy <= -0.01) {
												if ( AxXGz <= 0.0) {
													if ( AyXGz <= 0.01) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( GyXGz <= -0.02) {
											if ( AzXGz <= 0.05) {
												if ( AzXGy <= -0.01) {
													if ( GxXGz <= 0.01) {
														if ( Az_squared <= -0.21) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									return 2;
								}
							}
						}
					}
					else {
						if ( AxXGx <= -0.14) {
							return 2;
						}
						else {
							if ( Gx_squared <= -0.12) {
								return 2;
							}
							else {
								return 2;
							}
						}
					}
				}
			}
		}
	}
	else {
		if ( AyXAz <= -0.54) {
			if ( Ay <= 0.82) {
				if ( GxXGz <= -0.1) {
					if ( GxXGz <= -0.28) {
						if ( Ax_squared <= 0.45) {
							if ( AzXGy <= -0.4) {
								return 2;
							}
							else {
								if ( Ax_squared <= -0.1) {
									return 0;
								}
								else {
									if ( Gx_squared <= 0.0) {
										return 1;
									}
									else {
										if ( AyXGx <= 1.34) {
											return 2;
										}
										else {
											return 2;
										}
									}
								}
							}
						}
						else {
							if ( AzXGx <= -0.47) {
								return 2;
							}
							else {
								return 1;
							}
						}
					}
					else {
						if ( Ax <= -3.24) {
							return 0;
						}
						else {
							if ( AzXGx <= -0.4) {
								return 1;
							}
							else {
								if ( Gy_squared <= 0.03) {
									if ( AzXGy <= 0.23) {
										if ( AxXGz <= 0.0) {
											if ( AzXGx <= -0.22) {
												if ( GyXGz <= 0.01) {
													if ( Gx <= -1.14) {
														return 0;
													}
													else {
														if ( AyXGx <= 0.47) {
															return 0;
														}
														else {
															if ( Gz_squared <= -0.03) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AzXGy <= 0.0) {
													if ( GxXGy <= 0.01) {
														return 2;
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Az_squared <= -0.07) {
												if ( Gx <= -1.02) {
													return 0;
												}
												else {
													if ( AzXGy <= 0.0) {
														return 0;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 0;
									}
								}
								else {
									return 2;
								}
							}
						}
					}
				}
				else {
					if ( Gz_squared <= -0.0) {
						if ( AxXAz <= -1.35) {
							return 0;
						}
						else {
							if ( Ay <= -0.73) {
								if ( Gx_squared <= -0.09) {
									if ( AxXAy <= 0.11) {
										if ( GyXGz <= 0.03) {
											if ( GxXGz <= -0.03) {
												return 0;
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										return 0;
									}
								}
								else {
									return 2;
								}
							}
							else {
								if ( GyXGz <= -0.01) {
									if ( AyXGz <= 0.23) {
										if ( GxXGy <= 0.01) {
											return 0;
										}
										else {
											return 2;
										}
									}
									else {
										if ( AxXGz <= -0.28) {
											return 2;
										}
										else {
											if ( AxXAz <= 0.01) {
												return 0;
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if ( Gx_squared <= -0.13) {
										return 2;
									}
									else {
										return 0;
									}
								}
							}
						}
					}
					else {
						if ( AxXGy <= 0.11) {
							if ( AyXAz <= -0.55) {
								if ( AyXGz <= -0.55) {
									if ( Ax_squared <= -0.08) {
										if ( GxXGy <= -0.02) {
											return 2;
										}
										else {
											if ( AzXGx <= 0.0) {
												return 2;
											}
											else {
												if ( AxXGy <= -0.02) {
													return 0;
												}
												else {
													if ( AxXGx <= 0.01) {
														if ( AyXAz <= -0.6) {
															if ( AyXAz <= -0.66) {
																return 2;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( Gz <= 1.14) {
											if ( AxXGx <= 0.06) {
												if ( AxXGy <= 0.08) {
													if ( Gy <= -0.18) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											if ( AzXGz <= 0.36) {
												return 0;
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( GxXGz <= 0.13) {
										return 0;
									}
									else {
										return 2;
									}
								}
							}
							else {
								return 2;
							}
						}
						else {
							if ( Az_squared <= -0.01) {
								return 2;
							}
							else {
								return 2;
							}
						}
					}
				}
			}
			else {
				if ( AxXGz <= -0.07) {
					if ( Gx_squared <= 0.73) {
						if ( Gy <= 1.39) {
							if ( GxXGy <= -0.02) {
								if ( Gz_squared <= 1.05) {
									if ( AxXGx <= 0.55) {
										if ( AxXGy <= -0.33) {
											return 2;
										}
										else {
											if ( GyXGz <= -0.26) {
												if ( AzXGx <= -0.19) {
													return 2;
												}
												else {
													if ( AyXGx <= 0.09) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Gy_squared <= -0.06) {
													if ( AyXAz <= -0.62) {
														if ( Az <= -1.28) {
															return 2;
														}
														else {
															if ( Gz_squared <= -0.04) {
																if ( GyXGz <= -0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gz <= -1.52) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXGz <= 0.6) {
														if ( AxXGy <= -0.19) {
															return 2;
														}
														else {
															if ( AyXGx <= 0.19) {
																return 2;
															}
															else {
																if ( AxXGx <= 0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									if ( GxXGz <= -1.15) {
										return 2;
									}
									else {
										if ( AyXAz <= -2.62) {
											return 1;
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( Ay_squared <= 0.16) {
									if ( Gx <= 1.12) {
										if ( Az_squared <= 0.04) {
											if ( Ay_squared <= -0.15) {
												if ( GxXGy <= 0.07) {
													if ( Gz <= -0.68) {
														if ( AxXAz <= -0.27) {
															return 2;
														}
														else {
															if ( AxXAz <= -0.03) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AyXGz <= 0.46) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AzXGz <= 0.25) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Gy_squared <= -0.13) {
													if ( AxXGz <= -0.11) {
														if ( GxXGz <= 0.16) {
															if ( AzXGz <= 0.53) {
																if ( Gy <= 0.24) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AzXGx <= 0.07) {
															if ( AxXAz <= -0.01) {
																return 2;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AyXGy <= 0.46) {
														if ( AxXGz <= -0.08) {
															if ( Az <= -0.13) {
																if ( AxXAz <= 0.21) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXAy <= 0.68) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
										else {
											if ( Ax_squared <= -0.0) {
												if ( AxXAy <= 0.4) {
													if ( AzXGy <= 0.56) {
														if ( AxXGx <= 0.18) {
															if ( Ay <= 1.35) {
																if ( GyXGz <= -0.04) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGx <= -0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( Az_squared <= 0.12) {
														if ( Gx <= -0.7) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXAz <= -0.25) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( AyXAz <= -0.75) {
													if ( GxXGz <= -0.17) {
														return 2;
													}
													else {
														if ( Gz_squared <= -0.12) {
															return 2;
														}
														else {
															if ( Gy <= -1.57) {
																return 2;
															}
															else {
																if ( GxXGy <= 0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( GyXGz <= -0.28) {
											return 1;
										}
										else {
											if ( AxXAz <= 0.02) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( GxXGy <= 0.44) {
										if ( AyXAz <= -2.03) {
											return 2;
										}
										else {
											if ( Gz <= -0.93) {
												if ( Gx <= 1.18) {
													if ( AyXGy <= -0.07) {
														if ( AxXGy <= -0.02) {
															if ( Az <= -0.56) {
																if ( AxXAz <= -0.48) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AzXGx <= 0.16) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AzXGx <= 0.07) {
															if ( GxXGy <= 0.02) {
																return 2;
															}
															else {
																if ( AxXGy <= 0.19) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( GxXGz <= -0.07) {
													if ( GxXGz <= -0.18) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( Gy_squared <= -0.15) {
														if ( AyXAz <= -0.66) {
															if ( Gy_squared <= -0.16) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( Gz <= -0.65) {
															return 2;
														}
														else {
															if ( Gy_squared <= -0.14) {
																return 2;
															}
															else {
																if ( AxXAz <= 0.24) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Az_squared <= 1.86) {
											if ( AxXAz <= 0.16) {
												if ( AxXAz <= -0.05) {
													if ( Gy <= -2.9) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
							}
						}
						else {
							if ( Gx_squared <= 0.14) {
								if ( AxXAy <= -0.2) {
									return 2;
								}
								else {
									if ( Gz <= -3.55) {
										return 2;
									}
									else {
										if ( AxXGx <= 0.28) {
											if ( AxXAz <= 0.19) {
												if ( GxXGz <= 0.15) {
													if ( AzXGz <= 0.87) {
														if ( AyXAz <= -0.56) {
															if ( Gz_squared <= -0.1) {
																return 2;
															}
															else {
																if ( Ay_squared <= 0.29) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( Gy_squared <= 2.65) {
									if ( AzXGy <= -1.23) {
										return 2;
									}
									else {
										if ( AzXGy <= -0.88) {
											return 2;
										}
										else {
											if ( AyXAz <= -0.82) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									return 2;
								}
							}
						}
					}
					else {
						if ( Gx <= -3.16) {
							if ( AzXGz <= 5.45) {
								if ( Ax_squared <= 1.01) {
									if ( AyXGy <= 2.02) {
										if ( Az <= -0.6) {
											if ( AxXGx <= 2.26) {
												if ( AxXAy <= 0.66) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 0;
											}
										}
										else {
											return 0;
										}
									}
									else {
										return 2;
									}
								}
								else {
									return 1;
								}
							}
							else {
								return 2;
							}
						}
						else {
							if ( AzXGy <= -0.44) {
								if ( Az_squared <= 0.19) {
									return 2;
								}
								else {
									return 2;
								}
							}
							else {
								if ( AxXGy <= 0.15) {
									if ( AyXGy <= 0.25) {
										if ( AzXGy <= -0.07) {
											return 2;
										}
										else {
											if ( AxXAz <= -0.23) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									return 2;
								}
							}
						}
					}
				}
				else {
					if ( AzXGy <= -0.15) {
						if ( Gx_squared <= 0.79) {
							if ( AzXGy <= -0.26) {
								if ( GxXGz <= 0.06) {
									if ( GxXGz <= -0.44) {
										return 2;
									}
									else {
										if ( Ax_squared <= 0.08) {
											if ( AyXGz <= -0.88) {
												return 2;
											}
											else {
												if ( AxXGx <= 0.04) {
													if ( AzXGy <= -0.52) {
														if ( Az <= -0.88) {
															return 2;
														}
														else {
															if ( Gz_squared <= -0.09) {
																return 2;
															}
															else {
																if ( GyXGz <= -0.51) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AxXAy <= 0.19) {
															if ( Ay_squared <= -0.33) {
																return 2;
															}
															else {
																if ( Gz_squared <= -0.11) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXGz <= 0.04) {
																return 2;
															}
															else {
																if ( AxXGy <= 0.06) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AxXGx <= 0.01) {
										if ( GyXGz <= 0.53) {
											if ( AxXGy <= -0.04) {
												return 2;
											}
											else {
												if ( AyXGz <= -0.56) {
													return 2;
												}
												else {
													if ( GyXGz <= 0.3) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gx_squared <= -0.01) {
											if ( Ay_squared <= -0.17) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											if ( Gz_squared <= -0.11) {
												return 2;
											}
											else {
												if ( AyXAz <= -1.04) {
													return 2;
												}
												else {
													if ( AxXAy <= 0.2) {
														return 1;
													}
													else {
														return 2;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Ay_squared <= -0.21) {
									if ( Gz_squared <= -0.09) {
										return 2;
									}
									else {
										if ( AxXAz <= 0.08) {
											if ( Gy <= 0.67) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( Ay <= 1.47) {
										if ( AzXGz <= -0.29) {
											return 2;
										}
										else {
											if ( AyXAz <= -0.79) {
												return 2;
											}
											else {
												if ( GxXGz <= -0.14) {
													return 2;
												}
												else {
													if ( GyXGz <= 0.06) {
														if ( Gx_squared <= -0.02) {
															if ( AxXAz <= 0.09) {
																if ( AxXGx <= -0.02) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( AyXAz <= -1.0) {
											return 2;
										}
										else {
											return 2;
										}
									}
								}
							}
						}
						else {
							if ( Ay <= 1.49) {
								return 2;
							}
							else {
								if ( Az_squared <= 0.12) {
									return 2;
								}
								else {
									return 2;
								}
							}
						}
					}
					else {
						if ( Gx_squared <= -0.11) {
							if ( Az_squared <= 0.04) {
								if ( Ay_squared <= -0.25) {
									if ( Gz_squared <= -0.03) {
										if ( Gy <= -0.36) {
											return 2;
										}
										else {
											return 2;
										}
									}
									else {
										return 2;
									}
								}
								else {
									if ( Ay_squared <= 0.16) {
										if ( Gy <= -0.39) {
											if ( AzXGy <= 0.4) {
												if ( AyXGz <= 0.26) {
													if ( AxXGz <= 0.0) {
														return 1;
													}
													else {
														return 2;
													}
												}
												else {
													if ( GyXGz <= -0.18) {
														if ( Gz <= 1.14) {
															if ( AzXGz <= -0.25) {
																if ( AyXAz <= -0.77) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGy <= -0.03) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( Gy <= -0.49) {
															if ( AyXGz <= 0.35) {
																return 2;
															}
															else {
																if ( AyXGx <= -0.16) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Gz_squared <= -0.03) {
												if ( Az <= -0.45) {
													if ( AyXGy <= 0.06) {
														if ( Gx_squared <= -0.15) {
															return 2;
														}
														else {
															if ( Gz <= 0.5) {
																if ( AyXGy <= -0.01) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXGy <= -0.15) {
														if ( AyXGz <= -0.25) {
															return 1;
														}
														else {
															if ( GyXGz <= -0.05) {
																if ( AxXGx <= -0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														if ( AyXGy <= -0.05) {
															if ( AxXGx <= 0.05) {
																if ( AxXAz <= -0.14) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gx <= -0.4) {
																return 0;
															}
															else {
																if ( AxXGx <= -0.01) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gz_squared <= 0.14) {
													if ( AxXGy <= 0.01) {
														if ( Gy_squared <= -0.16) {
															return 0;
														}
														else {
															return 1;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( GyXGz <= 0.1) {
											if ( GxXGz <= -0.03) {
												return 2;
											}
											else {
												if ( Ay_squared <= 0.37) {
													if ( GyXGz <= -0.08) {
														return 2;
													}
													else {
														if ( Gy <= 0.22) {
															if ( Gx <= 0.2) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( Ax <= 0.52) {
									if ( AxXAz <= -0.02) {
										if ( Az <= -1.93) {
											return 0;
										}
										else {
											if ( Ay_squared <= -0.37) {
												return 2;
											}
											else {
												if ( AyXAz <= -1.15) {
													return 2;
												}
												else {
													if ( AyXGy <= -0.32) {
														return 2;
													}
													else {
														if ( GxXGy <= 0.02) {
															if ( AxXGz <= 0.13) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
												}
											}
										}
									}
									else {
										if ( AyXAz <= -1.0) {
											if ( Az <= -1.32) {
												return 2;
											}
											else {
												if ( Az_squared <= 0.1) {
													return 2;
												}
												else {
													if ( AxXGx <= -0.0) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( Gz_squared <= -0.01) {
												if ( GyXGz <= 0.0) {
													if ( Gy <= 0.12) {
														if ( AxXGx <= -0.01) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( Az_squared <= 0.39) {
										if ( Ay <= 1.25) {
											return 2;
										}
										else {
											return 0;
										}
									}
									else {
										return 0;
									}
								}
							}
						}
						else {
							if ( Az_squared <= 0.01) {
								if ( Ay_squared <= -0.25) {
									if ( Gz_squared <= -0.09) {
										return 2;
									}
									else {
										if ( Ax <= 0.46) {
											if ( AxXGz <= -0.0) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AyXGz <= 0.26) {
										if ( Gx_squared <= -0.09) {
											if ( Ay_squared <= 0.21) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											if ( AzXGx <= 0.55) {
												if ( AxXGx <= -0.03) {
													if ( Gy_squared <= -0.01) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AyXGy <= -0.1) {
														if ( AxXGx <= 0.05) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( GxXGz <= -0.1) {
											if ( Ay_squared <= -0.12) {
												return 2;
											}
											else {
												if ( GxXGy <= 0.92) {
													if ( AyXGy <= -1.01) {
														return 2;
													}
													else {
														if ( Az <= -0.2) {
															if ( AxXGz <= 0.19) {
																return 2;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AzXGy <= 0.24) {
												if ( Ay_squared <= 0.31) {
													if ( Gx_squared <= -0.06) {
														if ( AzXGz <= -0.26) {
															return 2;
														}
														else {
															if ( GxXGz <= 0.1) {
																if ( AxXGx <= -0.15) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AyXAz <= -0.76) {
															return 2;
														}
														else {
															if ( GxXGy <= 0.02) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( AxXGx <= -0.14) {
													return 1;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
							else {
								if ( AyXGx <= -1.8) {
									return 2;
								}
								else {
									if ( Ax <= -0.24) {
										if ( AzXGy <= 0.9) {
											if ( AyXAz <= -1.04) {
												if ( Gx <= -1.02) {
													return 2;
												}
												else {
													if ( AxXGx <= 0.0) {
														if ( AxXGz <= 0.1) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Ay_squared <= -0.17) {
													if ( AxXGy <= 0.04) {
														if ( AxXGz <= -0.03) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( GyXGz <= 0.01) {
														if ( Gz_squared <= 0.08) {
															if ( AyXGy <= 0.09) {
																if ( Gx_squared <= -0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXGz <= -0.04) {
															return 2;
														}
														else {
															if ( GyXGz <= 0.06) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Ay_squared <= -0.31) {
											if ( Gx_squared <= 0.51) {
												if ( AxXAy <= 0.64) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AyXGx <= -0.39) {
												if ( AxXAz <= -0.23) {
													return 2;
												}
												else {
													if ( Ay <= 1.33) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( GxXGy <= 0.03) {
													if ( Gz <= 0.85) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			if ( Gz <= 0.69) {
				if ( Ax <= 0.14) {
					if ( Gy <= -2.32) {
						if ( Gz_squared <= 0.32) {
							if ( Az <= -0.6) {
								if ( Gx_squared <= 0.71) {
									return 2;
								}
								else {
									return 0;
								}
							}
							else {
								if ( GxXGy <= -0.07) {
									return 2;
								}
								else {
									return 2;
								}
							}
						}
						else {
							if ( Gx_squared <= 0.24) {
								if ( AyXGx <= 0.08) {
									if ( Ax_squared <= -0.03) {
										if ( Gy <= -2.75) {
											return 0;
										}
										else {
											return 1;
										}
									}
									else {
										return 1;
									}
								}
								else {
									if ( AzXGx <= 0.1) {
										if ( GyXGz <= 1.77) {
											if ( AxXGz <= -0.38) {
												return 1;
											}
											else {
												if ( AzXGx <= 0.07) {
													return 1;
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( GxXGy <= 0.57) {
											if ( Gz <= -2.79) {
												if ( AyXGz <= 1.63) {
													if ( Gx <= -0.59) {
														if ( GyXGz <= 1.58) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
										else {
											if ( AzXGz <= 0.98) {
												if ( GxXGz <= 0.62) {
													return 1;
												}
												else {
													return 1;
												}
											}
											else {
												return 1;
											}
										}
									}
								}
							}
							else {
								if ( Gz_squared <= 1.62) {
									if ( Az_squared <= -0.06) {
										return 2;
									}
									else {
										return 1;
									}
								}
								else {
									return 2;
								}
							}
						}
					}
					else {
						if ( GxXGz <= 0.06) {
							if ( Gy <= -0.65) {
								if ( Az_squared <= 0.19) {
									if ( Gz <= 0.29) {
										if ( AzXGx <= -0.13) {
											if ( AzXGy <= 0.16) {
												return 1;
											}
											else {
												if ( AxXAz <= 0.31) {
													if ( AzXGy <= 0.59) {
														if ( AxXAz <= 0.04) {
															if ( Ax_squared <= -0.11) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( Ax <= -1.11) {
																return 2;
															}
															else {
																if ( Gx <= 1.98) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Gz_squared <= 0.32) {
												if ( AxXGz <= -0.06) {
													if ( AyXGy <= 0.45) {
														return 2;
													}
													else {
														if ( Ax <= 0.09) {
															if ( AzXGx <= -0.03) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AxXAy <= 0.03) {
														return 2;
													}
													else {
														if ( AyXAz <= 0.35) {
															if ( AzXGy <= 0.14) {
																if ( AzXGx <= 0.05) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Gx <= -0.1) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( AyXGy <= -0.52) {
											if ( GxXGy <= 0.08) {
												if ( Az_squared <= -0.17) {
													if ( AyXAz <= -0.14) {
														if ( AxXAz <= 0.08) {
															if ( GyXGz <= -0.21) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Ay <= 1.34) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AyXGx <= -0.1) {
												if ( AzXGz <= -0.13) {
													return 2;
												}
												else {
													if ( AyXGz <= 0.34) {
														return 0;
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( Gy_squared <= -0.04) {
													if ( Az_squared <= 0.09) {
														if ( AxXAz <= 0.05) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXGz <= -0.1) {
														return 0;
													}
													else {
														if ( AzXGy <= 0.43) {
															if ( GxXGy <= -0.01) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( Ay_squared <= -0.17) {
										if ( Ay <= -0.52) {
											if ( Gx <= 1.48) {
												if ( AxXGz <= -0.04) {
													return 0;
												}
												else {
													return 1;
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if ( GxXGz <= -0.13) {
											return 0;
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( AyXGy <= 0.72) {
									if ( Ay <= -0.78) {
										if ( AyXAz <= 0.52) {
											if ( AzXGy <= -0.07) {
												if ( AyXGz <= 1.06) {
													if ( AyXGz <= -0.2) {
														if ( GxXGy <= -0.01) {
															if ( Gx <= -0.41) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( GxXGy <= 0.14) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Ay_squared <= 0.37) {
													if ( GxXGy <= -0.02) {
														if ( AzXGx <= -0.1) {
															return 1;
														}
														else {
															if ( Gy_squared <= -0.13) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( AzXGy <= 0.04) {
															if ( AzXGz <= 0.18) {
																if ( Gx <= 0.04) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( Gx_squared <= 0.14) {
														if ( AzXGz <= -0.12) {
															return 0;
														}
														else {
															if ( Gz_squared <= -0.03) {
																if ( Gz_squared <= -0.07) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( GxXGz <= -0.09) {
												if ( Gx <= -2.97) {
													return 1;
												}
												else {
													if ( Gx_squared <= 0.31) {
														if ( Gz <= -2.4) {
															return 2;
														}
														else {
															if ( AxXAy <= 0.07) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( Ax_squared <= -0.12) {
															return 1;
														}
														else {
															if ( AyXAz <= 1.57) {
																return 2;
															}
															else {
																return 0;
															}
														}
													}
												}
											}
											else {
												if ( AzXGz <= 0.25) {
													if ( Ay_squared <= 0.31) {
														if ( GyXGz <= -0.03) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( AyXGz <= 1.03) {
											if ( AzXGy <= 0.24) {
												if ( AzXGz <= -0.01) {
													if ( Ay <= 1.28) {
														if ( AyXAz <= 0.03) {
															if ( Ay <= -0.22) {
																if ( AyXGz <= 0.39) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ay <= 1.23) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( AxXGy <= 0.07) {
																if ( Az_squared <= -0.13) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( AzXGz <= -0.19) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Gy <= -0.14) {
															if ( AyXGx <= -0.04) {
																if ( AyXGz <= 0.36) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXGz <= -0.02) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															if ( GyXGz <= -0.29) {
																return 1;
															}
															else {
																if ( AxXGx <= -0.07) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( Gx_squared <= 0.04) {
														if ( Az <= -0.92) {
															if ( Ay_squared <= -0.12) {
																if ( Gz_squared <= -0.09) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( Ay <= 1.28) {
																if ( Az <= 0.52) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gz_squared <= -0.11) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Az <= -0.09) {
															if ( AyXAz <= 0.77) {
																if ( Az_squared <= -0.08) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGy <= 0.1) {
																if ( Ay_squared <= 0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( GxXGz <= -0.26) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
											else {
												if ( Gz <= 0.33) {
													if ( AyXAz <= 0.55) {
														return 2;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Gx_squared <= -0.12) {
														if ( AxXAz <= 0.22) {
															if ( AyXGx <= 0.02) {
																return 1;
															}
															else {
																if ( GyXGz <= -0.11) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AzXGz <= 0.5) {
												if ( AzXGy <= -0.03) {
													if ( Ay_squared <= 0.06) {
														if ( AyXGz <= 1.21) {
															if ( Ay <= -0.7) {
																if ( Gz_squared <= 0.37) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGz <= 0.36) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GyXGz <= -0.55) {
																return 0;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AzXGz <= 0.19) {
															return 1;
														}
														else {
															return 1;
														}
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( AxXGx <= 0.03) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
								else {
									if ( Ay_squared <= 0.11) {
										if ( GyXGz <= -0.21) {
											if ( AyXGx <= 0.69) {
												if ( Ay <= 1.32) {
													return 2;
												}
												else {
													if ( Gz <= -1.14) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Gx_squared <= -0.05) {
											return 2;
										}
										else {
											if ( AxXGx <= 0.17) {
												return 2;
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
						else {
							if ( AzXGx <= -0.01) {
								if ( Gy_squared <= -0.13) {
									if ( AzXGz <= -0.14) {
										if ( AyXGx <= -0.25) {
											if ( AzXGy <= -0.06) {
												return 0;
											}
											else {
												if ( Ay_squared <= 0.16) {
													if ( AzXGx <= -0.21) {
														return 2;
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( Ay_squared <= -0.31) {
											return 2;
										}
										else {
											if ( Ay <= -0.85) {
												return 2;
											}
											else {
												if ( GxXGz <= 0.1) {
													if ( Gz <= 0.3) {
														return 2;
													}
													else {
														if ( AzXGz <= -0.06) {
															if ( AyXGz <= -0.24) {
																return 0;
															}
															else {
																if ( Ay_squared <= -0.08) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
														else {
															return 1;
														}
													}
												}
												else {
													if ( AxXAz <= 0.0) {
														return 2;
													}
													else {
														if ( Ay_squared <= -0.08) {
															return 2;
														}
														else {
															if ( AxXAy <= 0.3) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AyXGx <= -0.25) {
										if ( AyXGy <= -0.27) {
											if ( Ay_squared <= -0.08) {
												return 2;
											}
											else {
												if ( AxXAy <= -0.12) {
													return 2;
												}
												else {
													if ( AyXAz <= 0.44) {
														if ( Ax_squared <= -0.12) {
															return 0;
														}
														else {
															if ( AyXAz <= 0.26) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
													else {
														if ( AxXAy <= -0.03) {
															return 0;
														}
														else {
															return 2;
														}
													}
												}
											}
										}
										else {
											if ( Az_squared <= 0.15) {
												if ( AxXGz <= 0.02) {
													if ( AyXAz <= 0.67) {
														if ( Gy <= -0.69) {
															return 2;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( Ay_squared <= -0.19) {
											return 2;
										}
										else {
											if ( AxXGx <= -0.08) {
												return 2;
											}
											else {
												if ( Gx_squared <= -0.02) {
													if ( Az <= 0.26) {
														return 2;
													}
													else {
														return 0;
													}
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
							else {
								if ( Az <= -1.17) {
									if ( AyXGz <= 0.81) {
										if ( Ay_squared <= -0.21) {
											return 1;
										}
										else {
											return 2;
										}
									}
									else {
										if ( AxXAz <= 1.49) {
											return 2;
										}
										else {
											return 0;
										}
									}
								}
								else {
									if ( GyXGz <= 1.12) {
										if ( AzXGz <= 0.19) {
											if ( Ay_squared <= -0.1) {
												if ( Gx_squared <= 0.22) {
													if ( AxXGz <= -0.06) {
														return 2;
													}
													else {
														if ( Gy <= -0.16) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( GxXGy <= -0.08) {
													if ( AyXGy <= -1.39) {
														return 0;
													}
													else {
														if ( Gy <= 1.07) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( AyXAz <= -0.3) {
														return 2;
													}
													else {
														if ( AzXGx <= 0.2) {
															if ( AyXGy <= -0.2) {
																return 2;
															}
															else {
																if ( GxXGz <= 0.08) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
												}
											}
										}
										else {
											if ( Ay <= 1.37) {
												if ( Gy_squared <= 0.18) {
													if ( Ay <= -1.1) {
														return 0;
													}
													else {
														if ( Gz <= -3.89) {
															return 2;
														}
														else {
															if ( AxXGx <= 0.41) {
																if ( Az_squared <= -0.11) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( GxXGy <= 0.86) {
														if ( Az_squared <= -0.05) {
															if ( AzXGy <= 0.4) {
																return 2;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 1;
									}
								}
							}
						}
					}
				}
				else {
					if ( Az_squared <= 0.06) {
						if ( AxXGz <= -0.13) {
							if ( AyXGy <= 0.37) {
								if ( Gz <= -0.6) {
									if ( Az <= 0.3) {
										if ( AxXAz <= -0.3) {
											if ( Gy_squared <= -0.1) {
												if ( AyXGz <= 0.39) {
													return 1;
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Ay_squared <= -0.33) {
												if ( Gz <= -2.67) {
													return 2;
												}
												else {
													if ( Gx <= 1.33) {
														if ( Gy_squared <= -0.09) {
															if ( AxXAz <= -0.18) {
																return 2;
															}
															else {
																if ( Gx_squared <= -0.13) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AyXGz <= 0.48) {
													if ( AyXGz <= -0.87) {
														return 2;
													}
													else {
														if ( Ay <= 1.37) {
															if ( AyXGx <= -0.05) {
																if ( Gx_squared <= -0.14) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gy <= 0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXGy <= -0.15) {
																return 2;
															}
															else {
																if ( GxXGy <= 0.0) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
												else {
													if ( GxXGy <= -0.07) {
														return 2;
													}
													else {
														if ( AxXAz <= -0.17) {
															return 2;
														}
														else {
															if ( GxXGz <= -0.13) {
																return 2;
															}
															else {
																if ( AyXGz <= 0.57) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( AyXGz <= 0.98) {
											if ( Ay_squared <= -0.1) {
												if ( GxXGy <= -0.08) {
													if ( Ay_squared <= -0.85) {
														return 1;
													}
													else {
														return 2;
													}
												}
												else {
													if ( GxXGz <= 0.19) {
														if ( AyXGx <= -0.32) {
															return 2;
														}
														else {
															if ( AxXGx <= 0.53) {
																if ( AyXAz <= -0.42) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AzXGx <= -0.04) {
													if ( Gz <= -1.98) {
														return 2;
													}
													else {
														return 1;
													}
												}
												else {
													if ( Ay <= -0.68) {
														if ( Gx_squared <= 0.1) {
															if ( Gx <= -0.4) {
																return 0;
															}
															else {
																if ( Gz_squared <= -0.09) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( Ax <= 0.9) {
															if ( GxXGz <= 0.17) {
																if ( AxXAz <= 0.02) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( AyXGy <= 0.17) {
																return 2;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( AxXAz <= -0.19) {
										if ( GxXGz <= 0.01) {
											if ( AyXGy <= 0.23) {
												if ( GxXGz <= -0.06) {
													return 2;
												}
												else {
													if ( Gy_squared <= -0.15) {
														return 2;
													}
													else {
														return 1;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AyXGz <= 0.18) {
											if ( AyXGz <= -0.18) {
												return 2;
											}
											else {
												return 2;
											}
										}
										else {
											if ( AzXGy <= 0.08) {
												if ( Ay_squared <= 0.11) {
													if ( GxXGz <= -0.06) {
														return 2;
													}
													else {
														if ( Az_squared <= -0.23) {
															return 2;
														}
														else {
															if ( AyXGx <= -0.07) {
																if ( AyXGy <= 0.19) {
																	return 2;
																}
																else {
																	return 1;
																}
															}
															else {
																if ( Gy <= -0.24) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( GyXGz <= 1.13) {
									if ( AyXGx <= 0.62) {
										if ( Gy_squared <= 0.21) {
											if ( AzXGz <= -0.18) {
												return 0;
											}
											else {
												if ( Gx_squared <= 0.47) {
													if ( Gz_squared <= -0.0) {
														if ( AzXGx <= -0.0) {
															if ( AyXAz <= 0.25) {
																if ( AxXGy <= -0.25) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AxXAy <= -0.41) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AxXGz <= -0.26) {
																return 2;
															}
															else {
																if ( Gy_squared <= -0.07) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Gx <= 1.02) {
															if ( AyXAz <= -0.45) {
																return 2;
															}
															else {
																if ( GyXGz <= -0.24) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( Ay_squared <= -0.68) {
												return 2;
											}
											else {
												if ( AyXGz <= 0.66) {
													if ( AxXGy <= 1.46) {
														if ( AxXGz <= -0.17) {
															if ( AxXGy <= -1.4) {
																return 2;
															}
															else {
																if ( AyXAz <= -0.43) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( Gx <= 0.4) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
										}
									}
									else {
										if ( GxXGy <= 0.5) {
											return 1;
										}
										else {
											if ( Gz <= -1.38) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
								}
								else {
									if ( Gx <= -0.33) {
										if ( GyXGz <= 1.95) {
											return 1;
										}
										else {
											return 2;
										}
									}
									else {
										return 2;
									}
								}
							}
						}
						else {
							if ( Ay <= 1.29) {
								if ( AyXGx <= -0.05) {
									if ( Gy <= -1.26) {
										if ( AyXGy <= 0.91) {
											return 2;
										}
										else {
											return 2;
										}
									}
									else {
										if ( AxXGz <= 0.1) {
											if ( Ay <= -0.65) {
												if ( GxXGz <= -0.05) {
													return 1;
												}
												else {
													if ( GxXGy <= -0.03) {
														return 0;
													}
													else {
														if ( AyXGy <= 0.23) {
															if ( Az <= -0.06) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Az <= 0.41) {
													return 2;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( Ay_squared <= 0.26) {
												if ( Gy <= 0.39) {
													if ( Gx_squared <= -0.08) {
														if ( Gx_squared <= -0.09) {
															if ( AxXGx <= 0.28) {
																if ( Az <= -0.53) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														if ( AyXGz <= -0.28) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( Ay_squared <= 0.18) {
														if ( Gz_squared <= -0.07) {
															if ( AxXGz <= 0.2) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												if ( AxXGz <= 0.12) {
													return 2;
												}
												else {
													if ( GxXGy <= 0.19) {
														if ( AyXGy <= 0.73) {
															if ( GxXGz <= 0.11) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
									}
								}
								else {
									if ( GyXGz <= -0.08) {
										if ( Gx_squared <= -0.12) {
											if ( AzXGx <= 0.04) {
												if ( AyXGy <= 0.65) {
													if ( Ay_squared <= -0.23) {
														return 2;
													}
													else {
														if ( Ay_squared <= 0.18) {
															if ( AyXAz <= 0.15) {
																return 0;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Ay <= -0.75) {
													return 2;
												}
												else {
													if ( Ay_squared <= -0.27) {
														return 2;
													}
													else {
														if ( Gy <= -0.67) {
															return 1;
														}
														else {
															if ( Ay_squared <= -0.03) {
																return 1;
															}
															else {
																return 1;
															}
														}
													}
												}
											}
										}
										else {
											if ( Gx <= -1.06) {
												return 0;
											}
											else {
												if ( AyXGz <= -0.22) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										if ( AxXGy <= 0.1) {
											if ( Ay_squared <= -0.25) {
												if ( Ay <= 1.2) {
													if ( AxXAy <= -0.56) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( Ay_squared <= 0.29) {
													if ( AxXAz <= -0.13) {
														if ( AyXGx <= -0.02) {
															return 0;
														}
														else {
															if ( AyXGy <= -0.05) {
																return 2;
															}
															else {
																if ( Gz <= 0.4) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Az <= 0.88) {
															if ( Ay_squared <= -0.12) {
																return 2;
															}
															else {
																if ( Gz <= -0.56) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXAy <= -0.3) {
																if ( Gz_squared <= -0.12) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													if ( AyXGx <= 0.49) {
														return 2;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( GxXGy <= -0.63) {
												return 0;
											}
											else {
												if ( Gz_squared <= -0.1) {
													if ( Gx <= -0.61) {
														if ( Az <= -0.27) {
															return 0;
														}
														else {
															if ( Gz <= 0.39) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( GyXGz <= 0.01) {
															return 2;
														}
														else {
															if ( Ax_squared <= 0.45) {
																if ( Gx <= -0.12) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AyXGx <= 0.05) {
														return 2;
													}
													else {
														if ( Ay <= -0.82) {
															return 2;
														}
														else {
															if ( AxXAz <= 0.12) {
																if ( AyXGx <= 0.16) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( GyXGz <= -0.09) {
									if ( Gy <= -0.75) {
										if ( GxXGy <= 0.11) {
											return 0;
										}
										else {
											return 2;
										}
									}
									else {
										if ( Ay <= 1.41) {
											return 2;
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AyXAz <= -0.08) {
										if ( GyXGz <= 0.01) {
											if ( AxXGy <= -0.08) {
												return 0;
											}
											else {
												if ( AyXAz <= -0.42) {
													if ( GxXGy <= 0.01) {
														if ( Gz <= 0.42) {
															return 1;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													if ( AxXAz <= 0.02) {
														if ( AxXGy <= -0.05) {
															return 1;
														}
														else {
															if ( GyXGz <= -0.05) {
																return 0;
															}
															else {
																if ( Gx_squared <= -0.14) {
																	return 1;
																}
																else {
																	return 1;
																}
															}
														}
													}
													else {
														return 1;
													}
												}
											}
										}
										else {
											if ( AzXGx <= -0.04) {
												return 1;
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( AxXAy <= 0.55) {
											return 2;
										}
										else {
											if ( Ay <= 1.34) {
												return 0;
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
					}
					else {
						if ( Gz <= -0.61) {
							if ( AyXGx <= -0.11) {
								if ( AyXGz <= 0.32) {
									if ( Gx_squared <= -0.06) {
										return 1;
									}
									else {
										return 2;
									}
								}
								else {
									if ( Gz <= -0.72) {
										if ( Gz_squared <= -0.08) {
											return 0;
										}
										else {
											if ( AzXGy <= 1.51) {
												if ( Ay_squared <= -0.03) {
													if ( Gx_squared <= 0.59) {
														if ( AxXGy <= -0.2) {
															return 2;
														}
														else {
															return 0;
														}
													}
													else {
														return 1;
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( Gx_squared <= 1.51) {
													return 1;
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										return 2;
									}
								}
							}
							else {
								if ( AxXGx <= -0.51) {
									if ( Ax_squared <= -0.02) {
										return 2;
									}
									else {
										if ( AyXAz <= 0.48) {
											return 2;
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( Gy_squared <= -0.15) {
										return 2;
									}
									else {
										if ( Gx <= 3.06) {
											if ( Gz_squared <= -0.09) {
												return 2;
											}
											else {
												if ( AyXGy <= 0.3) {
													if ( AyXGx <= -0.03) {
														return 2;
													}
													else {
														if ( AyXAz <= 0.6) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
							}
						}
						else {
							if ( GxXGz <= 0.01) {
								if ( GyXGz <= -0.07) {
									if ( GyXGz <= -0.14) {
										return 2;
									}
									else {
										if ( Ay_squared <= -0.1) {
											if ( AyXGz <= -0.17) {
												if ( AyXGx <= 0.13) {
													if ( AxXAz <= -0.36) {
														return 1;
													}
													else {
														return 1;
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AxXGy <= 0.36) {
													if ( Ax_squared <= 0.2) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									if ( GyXGz <= 0.03) {
										if ( Ay_squared <= -0.01) {
											if ( Gx <= -0.21) {
												if ( Gz <= 0.35) {
													return 1;
												}
												else {
													return 2;
												}
											}
											else {
												if ( AxXGz <= -0.23) {
													return 0;
												}
												else {
													if ( GxXGy <= 0.01) {
														if ( AyXAz <= 0.77) {
															if ( Az_squared <= 0.15) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 1;
														}
													}
													else {
														if ( Gx <= -0.15) {
															return 1;
														}
														else {
															if ( Ax <= 0.25) {
																return 0;
															}
															else {
																if ( GxXGy <= 0.01) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AxXGz <= -0.09) {
											return 2;
										}
										else {
											if ( Ax_squared <= 0.04) {
												return 1;
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								if ( Ay_squared <= -0.15) {
									if ( Ax_squared <= -0.05) {
										return 1;
									}
									else {
										if ( AxXAy <= -0.84) {
											return 2;
										}
										else {
											if ( AyXGz <= -0.2) {
												return 2;
											}
											else {
												if ( AxXGz <= 0.21) {
													if ( GyXGz <= -0.11) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
								}
								else {
									if ( AzXGx <= -0.11) {
										return 2;
									}
									else {
										return 2;
									}
								}
							}
						}
					}
				}
			}
			else {
				if ( Ay <= 1.36) {
					if ( Gy_squared <= -0.12) {
						if ( AyXGz <= -0.2) {
							if ( AyXGy <= 0.07) {
								if ( AyXGx <= 0.25) {
									if ( Gy_squared <= -0.16) {
										if ( Az <= -1.71) {
											return 1;
										}
										else {
											if ( GyXGz <= -0.04) {
												if ( Gz <= 1.42) {
													if ( Gx <= 0.46) {
														if ( Az <= 1.34) {
															if ( AzXGx <= -0.06) {
																return 0;
															}
															else {
																if ( AzXGy <= -0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
											else {
												if ( AzXGz <= -0.45) {
													return 2;
												}
												else {
													if ( AxXAz <= 0.07) {
														if ( AzXGz <= -0.41) {
															return 0;
														}
														else {
															if ( AzXGx <= 0.01) {
																if ( AyXGz <= -0.6) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ay_squared <= 0.21) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Gy <= 0.04) {
															return 2;
														}
														else {
															if ( GyXGz <= -0.02) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Gx <= 1.55) {
											if ( Az_squared <= 0.48) {
												if ( AzXGx <= -0.17) {
													if ( AzXGz <= -0.42) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AxXGx <= 0.02) {
														if ( Gz_squared <= 0.09) {
															if ( AzXGy <= -0.1) {
																return 2;
															}
															else {
																if ( AyXAz <= 0.18) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( GxXGy <= -0.02) {
																return 2;
															}
															else {
																if ( AyXGy <= -0.1) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( AxXGy <= 0.13) {
															if ( AzXGz <= -0.39) {
																return 2;
															}
															else {
																if ( AzXGy <= -0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									if ( AyXAz <= -0.3) {
										if ( AxXGz <= -0.23) {
											return 1;
										}
										else {
											if ( Ay_squared <= 0.29) {
												if ( Gx <= -1.03) {
													if ( GxXGz <= -0.18) {
														if ( AyXGx <= 0.58) {
															if ( AyXGx <= 0.53) {
																return 0;
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
												else {
													if ( Gx <= -0.84) {
														if ( AxXAy <= 0.2) {
															if ( Gy_squared <= -0.16) {
																return 2;
															}
															else {
																if ( AxXAz <= 0.13) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 2;
											}
										}
									}
									else {
										if ( AyXAz <= 0.19) {
											if ( AxXGx <= -0.1) {
												if ( Gz <= 0.88) {
													if ( AxXAy <= -0.6) {
														if ( AzXGx <= 0.08) {
															if ( AzXGx <= -0.0) {
																return 1;
															}
															else {
																return 1;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( GxXGz <= -0.17) {
															if ( Gy_squared <= -0.16) {
																if ( AzXGx <= 0.13) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
														else {
															if ( Gx <= -0.85) {
																if ( Ay_squared <= -0.03) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AyXGz <= -0.73) {
														return 2;
													}
													else {
														if ( AzXGx <= 0.12) {
															if ( AzXGy <= -0.02) {
																return 2;
															}
															else {
																if ( Gz_squared <= 0.0) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Gy_squared <= -0.16) {
													if ( Gx_squared <= -0.02) {
														return 2;
													}
													else {
														if ( GxXGz <= -0.19) {
															return 2;
														}
														else {
															if ( AyXGz <= -0.48) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AxXAz <= 0.08) {
														if ( Gz_squared <= -0.0) {
															if ( GxXGz <= -0.18) {
																return 1;
															}
															else {
																if ( Gx_squared <= -0.03) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 0;
														}
													}
													else {
														return 2;
													}
												}
											}
										}
										else {
											if ( AzXGz <= -0.41) {
												if ( AxXGx <= 0.1) {
													if ( AzXGz <= -0.5) {
														if ( Ax_squared <= -0.11) {
															return 1;
														}
														else {
															return 2;
														}
													}
													else {
														if ( Gy_squared <= -0.15) {
															if ( AyXAz <= 0.73) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													return 1;
												}
											}
											else {
												if ( AxXAz <= 0.04) {
													if ( Ay <= -0.85) {
														return 2;
													}
													else {
														if ( GxXGz <= -0.13) {
															if ( AyXAz <= 0.3) {
																if ( Gz <= 0.86) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ay <= -0.7) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( AxXGy <= 0.01) {
																return 1;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AyXGz <= -0.43) {
														if ( Gz_squared <= 0.07) {
															if ( Ax_squared <= -0.12) {
																if ( Ay <= -0.78) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( AzXGz <= -0.23) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 1;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
								}
							}
							else {
								if ( Az_squared <= -0.19) {
									if ( Gx_squared <= -0.13) {
										if ( AzXGz <= -0.07) {
											if ( AzXGx <= 0.02) {
												if ( AyXGz <= -0.62) {
													if ( GxXGz <= 0.08) {
														if ( Gz <= 1.15) {
															if ( AxXGx <= 0.01) {
																if ( AzXGz <= -0.15) {
																	return 1;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXGx <= -0.11) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( GxXGy <= 0.01) {
																if ( AyXGy <= 0.23) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 2;
															}
														}
													}
													else {
														if ( Gz <= 1.3) {
															return 0;
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AyXGy <= 0.17) {
														if ( Ay <= -0.7) {
															if ( Ay_squared <= 0.13) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AyXGx <= -0.02) {
															if ( AxXAz <= 0.02) {
																if ( AxXAz <= 0.01) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( Ax <= -0.94) {
												return 2;
											}
											else {
												if ( AxXAz <= 0.1) {
													if ( AxXGz <= 0.44) {
														if ( AyXGy <= 0.28) {
															if ( Gy_squared <= -0.15) {
																if ( AxXAz <= 0.05) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gx <= 0.27) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 0;
													}
												}
												else {
													if ( AxXAz <= 0.14) {
														if ( GxXGy <= 0.0) {
															if ( Gz <= 1.04) {
																return 0;
															}
															else {
																if ( Gy_squared <= -0.15) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXAy <= -0.65) {
															return 0;
														}
														else {
															if ( GxXGz <= 0.05) {
																return 0;
															}
															else {
																return 0;
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( GyXGz <= -0.16) {
											return 2;
										}
										else {
											if ( GxXGy <= -0.02) {
												if ( GxXGy <= -0.02) {
													return 2;
												}
												else {
													return 2;
												}
											}
											else {
												if ( AzXGx <= 0.01) {
													if ( AzXGx <= -0.06) {
														return 2;
													}
													else {
														if ( AxXAy <= 0.05) {
															if ( AxXGx <= -0.21) {
																return 0;
															}
															else {
																return 0;
															}
														}
														else {
															return 0;
														}
													}
												}
												else {
													if ( AyXGx <= 0.38) {
														return 2;
													}
													else {
														if ( AyXGy <= 0.1) {
															return 2;
														}
														else {
															if ( Gy_squared <= -0.15) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AzXGz <= 0.22) {
										if ( GxXGy <= -0.01) {
											if ( Gz_squared <= -0.02) {
												return 2;
											}
											else {
												if ( GyXGz <= -0.17) {
													return 2;
												}
												else {
													if ( Gx <= 1.7) {
														if ( GxXGy <= -0.05) {
															return 2;
														}
														else {
															if ( Az_squared <= -0.16) {
																return 0;
															}
															else {
																if ( AyXAz <= 0.59) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											if ( GxXGz <= 0.04) {
												if ( Az <= -1.06) {
													return 1;
												}
												else {
													if ( AxXGz <= 0.34) {
														if ( Ax_squared <= -0.1) {
															if ( AxXGx <= -0.01) {
																if ( Gz <= 1.36) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Ay_squared <= -0.23) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AyXGz <= -0.49) {
																if ( Gx_squared <= 0.25) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGz <= -0.27) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AxXAy <= 0.66) {
													if ( AzXGx <= -0.05) {
														if ( AxXAy <= -0.36) {
															return 2;
														}
														else {
															if ( Gy <= -0.21) {
																if ( GyXGz <= -0.1) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																if ( Gz <= 0.94) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( GxXGy <= -0.0) {
															if ( AxXAz <= -0.04) {
																if ( AzXGz <= -0.23) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AyXGy <= 0.19) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															if ( Ay_squared <= -0.01) {
																return 0;
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													return 0;
												}
											}
										}
									}
									else {
										if ( AxXAz <= 0.18) {
											if ( AzXGx <= 0.08) {
												if ( AyXAz <= -0.43) {
													if ( AxXAz <= -0.01) {
														return 0;
													}
													else {
														if ( AxXGz <= 0.07) {
															if ( AxXGz <= -0.08) {
																return 2;
															}
															else {
																return 2;
															}
														}
														else {
															if ( AxXGz <= 0.11) {
																return 0;
															}
															else {
																if ( AxXGy <= -0.07) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
													}
												}
												else {
													return 2;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AxXGz <= 0.36) {
												return 2;
											}
											else {
												return 2;
											}
										}
									}
								}
							}
						}
						else {
							if ( Ay_squared <= -0.29) {
								if ( AxXAz <= 0.12) {
									if ( Gx_squared <= 0.12) {
										if ( Gz_squared <= -0.01) {
											return 2;
										}
										else {
											if ( Gx_squared <= -0.14) {
												return 2;
											}
											else {
												if ( Gy_squared <= -0.16) {
													return 2;
												}
												else {
													return 2;
												}
											}
										}
									}
									else {
										return 2;
									}
								}
								else {
									return 2;
								}
							}
							else {
								if ( Gz <= 1.32) {
									if ( AxXGx <= -0.03) {
										return 2;
									}
									else {
										if ( AzXGz <= -0.04) {
											if ( Gy_squared <= -0.16) {
												return 1;
											}
											else {
												return 1;
											}
										}
										else {
											return 2;
										}
									}
								}
								else {
									return 2;
								}
							}
						}
					}
					else {
						if ( AzXGy <= -0.63) {
							if ( AyXGz <= 0.25) {
								if ( AxXAz <= -0.02) {
									if ( Ay_squared <= -0.23) {
										if ( Gz <= 5.96) {
											if ( Gx_squared <= 1.97) {
												if ( Az <= -3.76) {
													return 1;
												}
												else {
													if ( AyXGy <= -1.27) {
														return 0;
													}
													else {
														if ( Gz_squared <= 0.06) {
															return 1;
														}
														else {
															if ( AxXAy <= -0.37) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
									else {
										if ( AyXGz <= -9.44) {
											return 0;
										}
										else {
											if ( AzXGx <= 1.41) {
												if ( AyXAz <= 0.84) {
													if ( Gy_squared <= 0.61) {
														return 1;
													}
													else {
														return 2;
													}
												}
												else {
													if ( AzXGz <= -1.03) {
														if ( AxXGz <= 0.73) {
															return 1;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 1;
											}
										}
									}
								}
								else {
									if ( Ay_squared <= -0.12) {
										if ( AyXAz <= 0.64) {
											return 2;
										}
										else {
											if ( AxXAy <= 0.35) {
												return 0;
											}
											else {
												return 1;
											}
										}
									}
									else {
										if ( AxXGx <= -0.01) {
											return 0;
										}
										else {
											if ( Ay_squared <= 3.47) {
												if ( AyXGz <= -0.64) {
													if ( AxXGx <= 1.16) {
														return 2;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
									}
								}
							}
							else {
								return 2;
							}
						}
						else {
							if ( Ay_squared <= -0.35) {
								if ( Ay <= 0.79) {
									if ( AxXAy <= 0.8) {
										if ( AyXAz <= 0.61) {
											if ( AxXGx <= 0.37) {
												if ( Gy_squared <= 2.53) {
													if ( AxXGx <= 0.18) {
														if ( AxXGy <= 0.71) {
															if ( Gz_squared <= -0.04) {
																return 2;
															}
															else {
																if ( AxXGx <= 0.09) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												return 2;
											}
										}
										else {
											if ( AxXGy <= -0.45) {
												return 2;
											}
											else {
												return 0;
											}
										}
									}
									else {
										return 0;
									}
								}
								else {
									if ( Ax <= -0.89) {
										return 2;
									}
									else {
										if ( AzXGz <= -0.19) {
											if ( AyXGx <= 0.48) {
												if ( AxXGy <= -0.02) {
													return 2;
												}
												else {
													if ( Gy_squared <= 0.35) {
														return 2;
													}
													else {
														return 2;
													}
												}
											}
											else {
												return 2;
											}
										}
										else {
											return 2;
										}
									}
								}
							}
							else {
								if ( GyXGz <= 0.18) {
									if ( AyXGy <= -0.4) {
										if ( AyXGx <= -0.18) {
											if ( AxXGx <= -0.09) {
												return 2;
											}
											else {
												if ( AyXGx <= -0.47) {
													return 0;
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( AxXAz <= 0.01) {
												if ( AxXAy <= 0.56) {
													if ( AzXGx <= 0.17) {
														if ( AxXAz <= -0.07) {
															return 0;
														}
														else {
															return 2;
														}
													}
													else {
														return 2;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if ( Ay <= -0.79) {
													return 2;
												}
												else {
													if ( AzXGz <= -0.16) {
														if ( AzXGx <= 0.04) {
															return 2;
														}
														else {
															return 1;
														}
													}
													else {
														if ( GxXGy <= -0.13) {
															return 1;
														}
														else {
															if ( AxXGy <= 0.05) {
																if ( AxXAy <= 0.37) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( AzXGx <= 0.03) {
																	return 0;
																}
																else {
																	return 1;
																}
															}
														}
													}
												}
											}
										}
									}
									else {
										if ( Gx <= -1.46) {
											if ( AxXGz <= -0.0) {
												return 1;
											}
											else {
												if ( GxXGz <= -0.32) {
													if ( AxXGy <= -3.56) {
														return 1;
													}
													else {
														if ( AxXGy <= -0.83) {
															return 0;
														}
														else {
															if ( GyXGz <= -0.19) {
																if ( Az <= -0.78) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 0;
															}
														}
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											if ( Gy_squared <= -0.08) {
												if ( AyXGx <= 0.08) {
													if ( Gx_squared <= -0.12) {
														if ( GyXGz <= -0.14) {
															if ( AzXGy <= -0.12) {
																return 2;
															}
															else {
																if ( AxXAz <= 0.08) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
														else {
															return 2;
														}
													}
													else {
														if ( AxXGy <= -0.02) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
												else {
													if ( Ax <= 0.36) {
														if ( Az_squared <= -0.19) {
															return 1;
														}
														else {
															if ( AzXGz <= -0.38) {
																return 1;
															}
															else {
																if ( Ax_squared <= -0.12) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( GxXGz <= -0.14) {
															return 2;
														}
														else {
															return 2;
														}
													}
												}
											}
											else {
												if ( Gy <= -3.67) {
													return 2;
												}
												else {
													if ( AxXAy <= 0.07) {
														if ( Gz_squared <= 0.09) {
															if ( AxXAz <= -0.32) {
																return 1;
															}
															else {
																if ( AyXGx <= -0.19) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															if ( AyXAz <= -0.26) {
																return 0;
															}
															else {
																if ( AyXGx <= 0.67) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
														}
													}
													else {
														if ( AyXGx <= 0.29) {
															if ( AxXGx <= -0.01) {
																if ( GxXGz <= 0.34) {
																	return 2;
																}
																else {
																	return 0;
																}
															}
															else {
																if ( Gx <= -0.4) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
														}
														else {
															return 2;
														}
													}
												}
											}
										}
									}
								}
								else {
									if ( AxXGx <= 0.36) {
										if ( AxXGz <= 3.0) {
											if ( Ax <= 1.33) {
												if ( GxXGy <= -0.04) {
													if ( AyXAz <= 0.42) {
														if ( GxXGz <= -0.3) {
															if ( GyXGz <= 1.8) {
																if ( AxXAz <= -0.0) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 1;
															}
														}
														else {
															if ( AyXGy <= -0.83) {
																return 2;
															}
															else {
																if ( AxXGy <= 0.11) {
																	return 1;
																}
																else {
																	return 2;
																}
															}
														}
													}
													else {
														if ( Gx <= -2.13) {
															return 1;
														}
														else {
															if ( AzXGy <= -0.34) {
																if ( AxXGz <= -0.05) {
																	return 0;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
													}
												}
												else {
													if ( AxXGz <= 0.55) {
														if ( Ax_squared <= -0.07) {
															if ( AyXAz <= 0.53) {
																if ( AxXGx <= 0.05) {
																	return 2;
																}
																else {
																	return 2;
																}
															}
															else {
																return 2;
															}
														}
														else {
															if ( AzXGx <= -0.09) {
																return 2;
															}
															else {
																return 2;
															}
														}
													}
													else {
														return 2;
													}
												}
											}
											else {
												if ( AxXAy <= -1.15) {
													if ( Gx <= -1.09) {
														return 2;
													}
													else {
														return 2;
													}
												}
												else {
													return 2;
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										if ( Gx <= 0.89) {
											return 2;
										}
										else {
											if ( GxXGy <= 0.37) {
												return 0;
											}
											else {
												if ( Az_squared <= -0.19) {
													return 1;
												}
												else {
													return 2;
												}
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if ( Gx_squared <= -0.12) {
						if ( AyXGy <= -0.52) {
							if ( Az <= 0.26) {
								if ( AxXAy <= -0.15) {
									return 1;
								}
								else {
									if ( GxXGy <= -0.0) {
										if ( AxXGx <= -0.0) {
											return 1;
										}
										else {
											return 0;
										}
									}
									else {
										if ( Gy_squared <= 0.08) {
											if ( AxXAy <= 0.03) {
												return 0;
											}
											else {
												if ( Gy <= -0.93) {
													if ( AxXGz <= 0.09) {
														if ( AyXGx <= -0.1) {
															return 0;
														}
														else {
															if ( AyXGz <= 0.57) {
																if ( AzXGz <= -0.16) {
																	return 0;
																}
																else {
																	return 0;
																}
															}
															else {
																return 0;
															}
														}
													}
													else {
														return 0;
													}
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
								}
							}
							else {
								if ( Gy <= -1.42) {
									return 2;
								}
								else {
									if ( AzXGz <= -0.06) {
										if ( AxXGx <= -0.01) {
											if ( AyXGy <= -0.68) {
												return 0;
											}
											else {
												if ( AxXAy <= -0.09) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if ( AxXAz <= 0.06) {
												if ( Gy_squared <= 0.01) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												if ( AzXGy <= 0.08) {
													return 0;
												}
												else {
													if ( Gy <= -0.96) {
														if ( Gy_squared <= 0.04) {
															return 0;
														}
														else {
															return 0;
														}
													}
													else {
														return 0;
													}
												}
											}
										}
									}
									else {
										if ( AxXGz <= -0.19) {
											return 0;
										}
										else {
											if ( AxXAy <= 0.17) {
												if ( AyXGx <= -0.02) {
													return 0;
												}
												else {
													return 0;
												}
											}
											else {
												if ( Ax_squared <= -0.11) {
													return 0;
												}
												else {
													return 0;
												}
											}
										}
									}
								}
							}
						}
						else {
							if ( Gy_squared <= -0.16) {
								return 1;
							}
							else {
								if ( AxXGz <= -0.04) {
									return 2;
								}
								else {
									if ( AxXGy <= 0.05) {
										if ( AyXAz <= -0.47) {
											return 0;
										}
										else {
											return 1;
										}
									}
									else {
										return 2;
									}
								}
							}
						}
					}
					else {
						if ( AyXGz <= 0.57) {
							return 1;
						}
						else {
							if ( GxXGy <= 0.18) {
								if ( AxXGz <= 0.19) {
									if ( Az_squared <= -0.22) {
										return 2;
									}
									else {
										if ( Az_squared <= -0.2) {
											return 0;
										}
										else {
											return 1;
										}
									}
								}
								else {
									return 2;
								}
							}
							else {
								if ( Gx <= -4.43) {
									return 1;
								}
								else {
									if ( AyXGz <= 2.22) {
										if ( GxXGy <= 0.23) {
											return 0;
										}
										else {
											if ( AxXGx <= -0.75) {
												return 0;
											}
											else {
												return 2;
											}
										}
									}
									else {
										return 2;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}