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

#include "vector4f.h"
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
    OBJIndex() = default;

    int GetVertexIndex();
    int GetTexCoordIndex();
    int GetNormalIndex();

    void SetVertexIndex(int val);
    void SetTexCoordIndex(int val);
    void SetNormalIndex(int val);

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
    bool equals(OBJIndex obj);

    bool operator==(const OBJIndex& other) const;
    bool operator<(const OBJIndex& other) const;
    bool operator>(const OBJIndex& other) const;
    bool operator!=(const OBJIndex& other) const;

    int hashCode() const;

    OBJIndex(const OBJIndex &other);

    OBJIndex(OBJIndex &&other);

    OBJIndex operator=
    (const OBJIndex& other);

    OBJIndex operator=
    (OBJIndex&& other);

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
    OBJModel(std::string fileName);

    IndexedModel ToIndexedModel();

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
            std::vector<std::string> data);

    //https://stackoverflow.com/questions/9435385/split-a-string-using-c11
    std::vector<std::string> split(const std::string& input,
                                   const std::string& regex);

    OBJIndex ParseOBJIndex(std::string token);
};


#endif // OBJMODEL_H
