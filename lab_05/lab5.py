import streamlit as st
import pandas as pd
import plotly.express as px
import glob
import os

st.set_page_config(page_title="Лабораторна робота 5", layout="wide")

@st.cache_data
def load_data():
    directory = "../lab_02/data"
    path = os.path.join(directory, "*.csv")
    all_files = glob.glob(path)
    
    if not all_files:
        st.error(f"Файли не знайдено за шляхом: {directory}. Перевірте структуру папок.")
        return pd.DataFrame()

    all_data = []
    noaa_to_name = {
        1: "Черкаська", 2: "Чернігівська", 3: "Чернівецька", 4: "Крим", 5: "Дніпропетровська",
        6: "Донецька", 7: "Івано-Франківська", 8: "Харківська", 9: "Херсонська", 10: "Хмельницька",
        11: "Київська", 12: "Кіровоградська", 13: "Луганська", 14: "Львівська", 15: "Миколаївська",
        16: "Одеська", 17: "Полтавська", 18: "Рівненська", 19: "Севастополь", 20: "Сумська",
        21: "Тернопільська", 22: "Закарпатська", 23: "Вінницька", 24: "Волинська", 25: "Запорізька",
        26: "Житомирська", 27: "Київ"
    }

    for file in all_files:
        try:
            with open(file, 'r') as f:
                lines = f.readlines()
            
            clean_rows = []
            for line in lines:
                line = line.replace('<pre>', '').replace('</pre>', '').replace('<br>', '').strip()
                if not line or 'year' in line.lower():
                    continue
                parts = line.split(',')
                if len(parts) >= 7:
                    clean_rows.append(parts[:7])

            temp_df = pd.DataFrame(clean_rows, columns=['Year', 'Week', 'SMN', 'SMT', 'VCI', 'TCI', 'VHI'])

            for col in temp_df.columns:
                temp_df[col] = pd.to_numeric(temp_df[col], errors='coerce')

            temp_df = temp_df.dropna(subset=['Year', 'VHI'])
            temp_df = temp_df[temp_df['VHI'] != -1]

            orig_id = int(os.path.basename(file).split('_')[2])
            temp_df['Province'] = noaa_to_name.get(orig_id, "Unknown")
            
            all_data.append(temp_df)
            
        except Exception as e:
            print(f"Помилка у файлі {file}: {e}")

    return pd.concat(all_data, ignore_index=True)

df = load_data()

if df.empty:
    st.stop()

def reset_filters():
    st.session_state.index_choice = 'VHI'
    st.session_state.prov_choice = 'Вінницька'
    st.session_state.week_range = (1, 52)
    st.session_state.year_range = (int(df['Year'].min()), int(df['Year'].max()))
    st.session_state.sort_asc = False
    st.session_state.sort_desc = False

if 'index_choice' not in st.session_state:
    reset_filters()

col1, col2 = st.columns([1, 3]) 

with col1:
    st.header("Параметри")
    st.button("Скинути фільтри", on_click=reset_filters)
    
    index_option = st.selectbox("Виберіть індекс:", ('VCI', 'TCI', 'VHI'), key='index_choice')
    
    provinces = sorted(df['Province'].unique())
    province_option = st.selectbox("Виберіть область:", provinces, key='prov_choice')
    
    week_range = st.slider("Інтервал тижнів:", 1, 52, key='week_range')
    
    min_year, max_year = int(df['Year'].min()), int(df['Year'].max())
    year_range = st.slider("Інтервал років:", min_value=min_year, max_value=max_year, key='year_range')
    
    st.markdown("---")
    st.subheader("Сортування даних")
    sort_asc = st.checkbox("За зростанням", key='sort_asc')
    sort_desc = st.checkbox("За спаданням", key='sort_desc')

filtered_df = df[
    (df['Year'] >= year_range[0]) & (df['Year'] <= year_range[1]) &
    (df['Week'] >= week_range[0]) & (df['Week'] <= week_range[1])
]

prov_df = filtered_df[filtered_df['Province'] == province_option].copy()

if sort_asc and sort_desc:
    st.warning("Оберіть лише один вид сортування.")
elif sort_asc:
    prov_df = prov_df.sort_values(by=index_option, ascending=True)
elif sort_desc:
    prov_df = prov_df.sort_values(by=index_option, ascending=False)

with col2:
    st.header(f"Аналіз індексу {index_option}")
    tab1, tab2, tab3 = st.tabs(["Таблиця даних", "Графік часового ряду", "Порівняння областей"])
    
    with tab1:
        st.subheader(f"Дані для області: {province_option}")
        st.dataframe(prov_df[['Year', 'Week', 'Province', index_option]], use_container_width=True)
        
    with tab2:
        st.subheader(f"Динаміка {index_option} для області {province_option}")
        plot_df = prov_df.sort_values(by=['Year', 'Week']) 
        plot_df['Time'] = plot_df['Year'].astype(str) + " - W" + plot_df['Week'].astype(str)
        
        fig1 = px.line(plot_df, x='Time', y=index_option, title=f"{index_option} з {year_range[0]} по {year_range[1]}")
        fig1.update_layout(xaxis_title="Рік - Тиждень", yaxis_title=index_option)
        st.plotly_chart(fig1, use_container_width=True)
        
    with tab3:
        st.subheader("Порівняння з іншими областями")
        st.markdown(f"Середнє значення **{index_option}** за тижні {week_range[0]}-{week_range[1]}, роки {year_range[0]}-{year_range[1]}")
        
        mean_df = filtered_df.groupby('Province')[index_option].mean().reset_index()
        mean_df['Колір'] = ['Обрана область' if p == province_option else 'Інші області' for p in mean_df['Province']]
        
        fig2 = px.bar(
            mean_df, x='Province', y=index_option, color='Колір',
            color_discrete_map={'Обрана область': 'red', 'Інші області': 'blue'},
            text_auto='.2f'
        )
        fig2.update_layout(xaxis=dict(tickmode='linear', tickangle=-45), xaxis_title="Область", yaxis_title=f"Середній {index_option}")
        st.plotly_chart(fig2, use_container_width=True)