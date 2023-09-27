#pragma once

#ifdef DATA_FOR_NETWORK
bool points_data[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };

// Threshold (14 �������)
bool NO_etalons[4] = { 0, 0, 0, 0 }; // ���������� ������� ���
bool AND_etalons[4] = { 0, 0, 0, 1 }; // ���������� � (����������)
bool NIMP_etalons[4] = { 0, 0, 1, 0 }; // �������� ������� 
bool FIRST_etalons[4] = { 0, 0, 1, 1 }; // ���������� ������� ������� ���������
bool NRIMP_etalons[4] = { 0, 1, 0, 0 }; // �������� ������� 
bool SECOND_etalons[4] = { 0, 1, 0, 1 }; // ���������� ������� ������� ���������
bool OR_etalons[4] = { 0, 1, 1, 1 }; // ���������� ��� (����������)
bool PIRS_etalons[4] = { 1, 0, 0, 0 }; // ������� �����
bool NFIRST_etalons[4] = { 1, 1, 0, 0 }; // ���������� ������� ������� ���������
bool NSECOND_etalons[4] = { 1, 0, 1, 0 }; // ���������� ������� ������� ���������
bool RIMP_etalons[4] = { 1, 0, 1, 1 }; // �������� ����������
bool IMP_etalons[4] = { 1, 1, 0, 1 }; // ����������
bool SHEFFER_etalons[4] = { 1, 1, 1, 0 }; // ������� �������
bool YES_etalons[4] = { 1, 1, 1, 1 }; // ���������� ������� ������

// Signal (2 �������)
bool XOR_etalons[4] = { 0, 1, 1, 0 }; // ����������� ���
bool EQ_etalons[4] = { 1, 0, 0, 1 }; // ���������� ������������

#endif