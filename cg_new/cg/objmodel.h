#ifndef OBJMODEL_H
#define OBJMODEL_H

/*
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
*/

#include <vector>
#include <utility> //make_pair
#include <map>
#include <string>
#include <QDebug>
#include <regex>
#include <fstream> //ifstream

#include "Vector4f.h"
#include "indexedmodel.h"

//Это действия, касающиеся директивы загрузчика
#if defined (_WIN32) || defined (_WIN64)
    #include <direct.h>
#elif defined (__APPLE__) || defined(__MACH__)
    #include <unistd.h>

#endif


// Класс, внутренний для OBJModel, объявлен в строке 11
class OBJIndex
{
public:
    int GetVertexIndex()   { return m_vertexIndex; }
    int GetTexCoordIndex() { return m_texCoordIndex; }
    int GetNormalIndex()   { return m_normalIndex; }

    void SetVertexIndex(int val)   { m_vertexIndex = val; }
    void SetTexCoordIndex(int val) { m_texCoordIndex = val; }
    void SetNormalIndex(int val)   { m_normalIndex = val; }

    /* По умолчанию все классы являются объектами наследниками
     * класса Object. Описанные ниже 2 метода являются пере-
     * определенными методами того суперкласса, для нас это не
     * ничего не значит, строчка 25
     *
     * На вход передается тот самый суперкласс, однако у нас
     * его нет, поэтому просто переопределим под OBJIndex и
     * любые другие, которые будут нужны
     */
    //@Override
    bool equals(OBJIndex obj) {
        return m_vertexIndex == obj.m_vertexIndex
                && m_texCoordIndex == obj.m_texCoordIndex
                && m_normalIndex == obj.m_normalIndex;
    }

    int hashCode() {
        // было 2 final
        const int BASE = 17;
        const int MULTIPLIER = 31;

        int result = BASE;

        result = MULTIPLIER * result + m_vertexIndex;
        result = MULTIPLIER * result + m_texCoordIndex;
        result = MULTIPLIER * result + m_normalIndex;

        return result;
    }

    // В оригинале нет конструктора, странно
    //OBJIndex()

private:
    int m_vertexIndex;
    int m_texCoordIndex;
    int m_normalIndex;
};

// Класс OBJModel, объявлен в строке 9
class OBJModel
{
public:
    OBJModel(std::string fileName)// throws IOException
    {
        m_hasTexCoords = false;
        m_hasNormals = false;

        std::ifstream in;

        char current_work_dir[FILENAME_MAX];
        char* (*fget)(char *, int);

        #if defined (_WIN32) || defined (_WIN64)
            fget = &_getcwd;
            char folders[10] = "\\objs\\";
        #elif defined (__APPLE__) && defined(__MACH__) || defined (__linux__)
            fget = &getcwd;
            char folders[10] = "/objs/";
        #endif

        fget(current_work_dir, sizeof(current_work_dir));

        // http://qaru.site/questions/124663/how-to-concatenate-two-strings-in-c
        char rfilename[sizeof(current_work_dir) +
                sizeof(fileName) + sizeof(folders)];
        strcpy (rfilename, current_work_dir) ;
        strcat (rfilename, folders) ;
        strcat (rfilename, fileName.c_str()) ;

        in.open(rfilename, std::ifstream::in);
        qDebug() << "\n objmodel.h. rfilename:" << rfilename;
        if (in.fail()) {
            return;
        }

        std::string line;

        while (!in.eof()) {
            std::getline(in, line);
            std::istringstream iss(line.c_str());

            std::vector<std::string> tokens = split(line, " ");

            tokens = RemoveEmptyStrings(tokens);

            if(tokens.size() == 0 || tokens[0] == "#") {
                continue;
            } else if(tokens[0] == "v") {
                // https://stackoverflow.com/questions/1012571/stdstring-to-float-or-double
                m_positions.push_back(Vector4f(
                                          std::stof(tokens[1]),
                                          std::stof(tokens[2]),
                                          std::stof(tokens[3]),
                                          1));
            } else if(tokens[0] == "vt") {
                m_texCoords.push_back(Vector4f(
                                          std::stof(tokens[1]),
                                          1.0f - std::stof(tokens[2]),
                                          0, 0));
            } else if(tokens[0] == "vn") {
                m_normals.push_back(Vector4f(
                                  std::stof(tokens[1]),
                                  std::stof(tokens[2]),
                                  std::stof(tokens[3]),0));
            } else if(tokens[0] == "f") {
                /*
                 * Я бы писал без цикла
                 */
                for(int i = 0; i < tokens.size() - 3; i++) {
                    m_indices.push_back(ParseOBJIndex(tokens[1]));
                    m_indices.push_back(ParseOBJIndex(tokens[2 + i]));
                    m_indices.push_back(ParseOBJIndex(tokens[3 + i]));
                }
            }
        }
        in.close();
    }

    IndexedModel ToIndexedModel() {
        IndexedModel result;
        IndexedModel normalModel;
        std::map<OBJIndex, int> resultIndexMap;
        std::map<int, int> normalIndexMap;
        std::map<int, int> indexMap;

        for(int i = 0; i < m_indices.size(); i++) {
            OBJIndex currentIndex = m_indices[i];

            Vector4f currentPosition = m_positions[currentIndex.GetVertexIndex()];
            Vector4f currentTexCoord;
            Vector4f currentNormal;

            if(m_hasTexCoords) {
                currentTexCoord = m_texCoords[currentIndex.GetTexCoordIndex()];
            } else {
                currentTexCoord = Vector4f(0,0,0,0);
            }

            if(m_hasNormals) {
                currentNormal = m_normals[currentIndex.GetNormalIndex()];
            } else {
                currentNormal = Vector4f(0,0,0,0);
            }

            int modelVertexIndex;
            /* В оригинале тут стоит проверка, что Integer == NULL, 153 строчка,
             * что значит, что map не содержит элемента
             * под введенным индексом, я заменил как написано тут
             * https://stackoverflow.com/questions/1810258/finding-a-nonexisting-key-in-a-stdmap
             */
            if(resultIndexMap.find(currentIndex) == resultIndexMap.end()) {
                modelVertexIndex = result.GetPositions().size();
                /* В оригинале было put(K k, V v) - помещает элемент
                 *  в вызывающее отображение, переписывая любое
                 *  предшествующее значение, ассоциированное с ключом.
                 *  Возвращает null, если ключ ранее не существовал.
                 *  В противном случае возвращается предыдущее
                 *  значение, связанное с ключом.
                 * Взято из http://developer.alexanderklimov.ru/android/java/map.php
                 *
                 * Аналогия для плюсов взята отсюда. Ctrl+f - mp.insert(make_pair(num_1, num_2));
                 * https://codelessons.ru/cplusplus/map-v-c-chto-eto-i-kak-s-etim-rabotat.html
                 */
                resultIndexMap.insert(std::make_pair(currentIndex, modelVertexIndex));

                result.PushPosition(currentPosition); // Вершины
                result.PushTexCoords(currentTexCoord); // Тектуры
                if(m_hasNormals)
                    result.PushNormal(currentNormal); // Нормали
            } else {
               modelVertexIndex = resultIndexMap[currentIndex];
            }

            // Аналогично верхнему случаю
            int normalModelIndex;

            if(normalIndexMap.find(currentIndex.GetVertexIndex()) == normalIndexMap.end())
            {
                normalModelIndex = normalModel.GetPositions().size();
                normalIndexMap.insert(std::make_pair(currentIndex.GetVertexIndex(), normalModelIndex));

                normalModel.PushPosition(currentPosition); // вершины в подготовительной модели
                normalModel.PushTexCoords(currentTexCoord); // текстуры в подготовительной
                normalModel.PushNormal(currentNormal);     // нормали в подготовительной
                normalModel.PushTangent(Vector4f(0,0,0,0));// касательные в подготовительной
            } else {
                normalModelIndex = normalIndexMap[currentIndex.GetVertexIndex()];
            }

            result.PushIndice(modelVertexIndex);      // индексы в готовую
            normalModel.PushIndice(normalModelIndex); // индексы в подготовительную
            indexMap.insert(std::make_pair(modelVertexIndex, normalModelIndex));

        }

        if(!m_hasNormals) {
            normalModel.calcNormals();
            result.setNormals(normalModel.GetNormals());
        }

        normalModel.calcTangents();
        result.SetTangents(normalModel.GetTangents());

        return result;
    }

private:

    std::vector<Vector4f> m_positions;
    std::vector<Vector4f> m_texCoords;
    std::vector<Vector4f> m_normals;
    std::vector<OBJIndex> m_indices;
    bool        m_hasTexCoords;
    bool        m_hasNormals;

    /* private static
     * гуглится по запросу "Для чего пишут модификаторы private
     * static для переменных"
     */
    /* String[] был заменен на std::vector<std::string>
     * см. строчку 58
     */
    static std::vector<std::string> RemoveEmptyStrings(
            std::vector<std::string> data) {
        std::vector<std::string> result;

        for(int i = 0; i < data.size(); i++)
            if(data[i] != "")
                result.push_back(data[i]);
        return result;
    }

    //https://stackoverflow.com/questions/9435385/split-a-string-using-c11
    std::vector<std::string> split(const std::string& input,
                                   const std::string& regex) {
        // passing -1 as the submatch index parameter performs splitting
        std::regex re(regex);
        std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
        return {first, last};
    }

    OBJIndex ParseOBJIndex(std::string token) {
        std::vector<std::string> values = split(token, "/");

        OBJIndex result;
        // https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
        result.SetVertexIndex(std::stoi(values[0]) - 1);

        if(values.size() > 1) {
            if(!values[1].empty()) {
                m_hasTexCoords = true;
                result.SetTexCoordIndex(std::stoi(values[1]) - 1);
            }

            if(values.size() > 2) {
                m_hasNormals = true;
                result.SetNormalIndex(std::stoi(values[2]) - 1);
            }
        }
        return result;
    }
};


#endif // OBJMODEL_H
